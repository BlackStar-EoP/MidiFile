#pragma once

#include "Midi.h"
#include "MidiHeaderChunk.h"
#include "MidiTrackChunk.h"
#include "MidiEvents/MidiEvent.h"
#include <vector>
#include <sstream>

class MidiFile
{
public:

	MidiFile(const std::string& file_name)
	: m_bpm(120)
	{
		unsigned int file_size;
		uint8_t* data = read_file(file_name, file_size);
		
		if (data && file_size > MidiHeaderChunk::HEADER_PARSE_SIZE)
		{
			int header_location = m_header_chunk.header_location(data);
			if (header_location > -1)
			{
				parse_track_chunks(m_track_chunks, data, m_header_chunk.get_num_tracks(), header_location);
			}
		}
		delete data;
		calculate_real_times();
	}

	bool save(const std::string& file_name)
	{
		return true;
	}

	void dump_tracks(const std::string& location)
	{
		for (unsigned int i = 0; i < m_track_chunks.size(); ++i)
		{
			MidiTrackChunk* chunk = m_track_chunks[i];
			std::vector<MidiEvent*>& events = chunk->events();

			std::stringstream ss;
			ss << location << "/TRACK-" << chunk->track_number() << ".txt";

			FILE* fp; fopen_s(&fp, ss.str().c_str(), "w+");
			if (fp != nullptr)
			{
				for (unsigned int j = 0; j < events.size(); ++j)
				{
					fprintf(fp, events[j]->to_string().c_str());
				}
				fclose(fp);
			}
		}
	}

	~MidiFile()
	{
		for (unsigned int i = 0; i < m_track_chunks.size(); ++i)
		{
			delete m_track_chunks[i];
		}
	}

	MidiHeaderChunk& header_chunk()
	{
		return m_header_chunk;
	}

	std::vector<MidiTrackChunk*>& track_chunks()
	{
		return m_track_chunks;
	}

	uint32_t bpm() const
	{
		return m_bpm;
	}

	float length()
	{
		float length = 0.0f;
		for (unsigned int i = 0; i < m_track_chunks.size(); ++i)
		{
			MidiTrackChunk* track_chunk = m_track_chunks[i];
			if (track_chunk->events().size() > 0)
			{
				MidiEvent* e = track_chunk->events().back();
				if (e->event_type() == MidiEvent::META && (static_cast<MidiMetaEvent*>(e)->meta_event_type() == MidiMetaEvent::END_OF_TRACK))
				{
					if (e->real_time() > length)
					{
						length = e->real_time();
					}
				}
			}
		}
		return length;
	}

private:
	void calculate_real_times()
	{
		std::vector<MidiSetTempoMetaEvent*> tempo_events;
		for (unsigned int i = 0; i < m_track_chunks.size(); ++i)
		{
			MidiTrackChunk* chunk = m_track_chunks[i];
			std::vector<MidiEvent*>& events = chunk->events();

			for (unsigned int j = 0; j < events.size(); ++j)
			{
				MidiEvent* e = events[j];
				if (e->event_type() == MidiEvent::META)
				{
					MidiMetaEvent* me = static_cast<MidiMetaEvent*>(e);
					if (me->meta_event_type() == MidiMetaEvent::SET_TEMPO)
					{
						tempo_events.push_back(static_cast<MidiSetTempoMetaEvent*>(me));
					}
				}
			}
		}
		if (tempo_events.size() == 0)
		{
		}
		else if (tempo_events.size() == 1)
		{
			uint32_t microseconds_per_quarter_note = tempo_events[0]->microseconds_per_quarter_note();
			m_bpm = msqn_to_bpm(microseconds_per_quarter_note);
			uint16_t time_division = m_header_chunk.get_time_division();

			for (unsigned int i = 0; i < m_track_chunks.size(); ++i)
			{
				MidiTrackChunk* chunk = m_track_chunks[i];
				std::vector<MidiEvent*>& events = chunk->events();

				for (unsigned int j = 0; j < events.size(); ++j)
				{
					MidiEvent* e = events[j];
					TICKS event_time = e->song_time();
					float num_beats = event_time / static_cast<float>(time_division);
					float microseconds = num_beats * microseconds_per_quarter_note;
					float seconds = microseconds / 1000000;
					e->set_real_time(seconds);
				}
			}
		}
		else
		{
			// ohhh dear...
		}

	}

	uint32_t msqn_to_bpm(uint32_t microseconds_per_quarter_note) const
	{
		if ( (Midi::MICROSECONDS_PER_MINUTE % microseconds_per_quarter_note) != 0)
		{
			printf("bliep");
		}

		return Midi::MICROSECONDS_PER_MINUTE / microseconds_per_quarter_note;
	}

	uint32_t bpm_to_msqn(uint32_t bpm) const
	{
		if ( (Midi::MICROSECONDS_PER_MINUTE % bpm) != 0)
		{
			printf("bliep");
		}
		return Midi::MICROSECONDS_PER_MINUTE / bpm;
	}

	uint8_t* read_file(const std::string& file_name, unsigned int& file_size)
	{
		FILE* fp; fopen_s(&fp, file_name.c_str(), "rb");
		uint8_t* data = nullptr;
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			long size = ftell(fp);
			rewind(fp);

			if (size > 0)
			{
				data = new uint8_t[size];
				fread(data, sizeof(uint8_t), size, fp);
			}	
			fclose(fp);
			file_size = size;
			return data;
		}
		file_size = 0;
		return nullptr;
	}

	bool parse_track_chunks(std::vector<MidiTrackChunk*>& track_chunks, uint8_t* data, uint16_t num_tracks, int header_location)
	{
		uint8_t* file_position = data + header_location + MidiHeaderChunk::SIZE;
		uint32_t current_track = 1;
		do
		{
			MidiTrackChunk* chunk = new MidiTrackChunk(current_track);

			if (!chunk->parse_header(file_position))
				return false;

			file_position += MidiTrackChunk::HEADER_SIZE;
			
			chunk->chunk_size = Midi::parse_uint32(file_position);
			file_position += sizeof(uint32_t);
			
			chunk->data = new uint8_t[chunk->chunk_size];
			memcpy(chunk->data, file_position, chunk->chunk_size);
			file_position += chunk->chunk_size;
			
			++current_track;
			track_chunks.push_back(chunk);
			if (!chunk->parse())
				return false;
		}
		while(current_track < num_tracks + 1u);
	
		//int file_size = file_position - data; // TODO verify
		return true;
	}

private:
	uint32_t m_bpm;
	MidiHeaderChunk m_header_chunk;
	std::vector<MidiTrackChunk*> m_track_chunks;
};