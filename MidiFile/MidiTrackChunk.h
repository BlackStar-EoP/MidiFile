#pragma once

#include <vector>

#include "Midi.h"
#include "MidiEvents/MidiEvent.h"

// Channel events
#include "MidiEvents/ChannelEvents/MidiNoteOffEvent.h"
#include "MidiEvents/ChannelEvents/MidiNoteOnEvent.h"
#include "MidiEvents/ChannelEvents/MidiAfterTouchEvent.h"
#include "MidiEvents/ChannelEvents/MidiControllerEvent.h"
#include "MidiEvents/ChannelEvents/MidiProgramChangeEvent.h"
#include "MidiEvents/ChannelEvents/MidiChannelAfterTouchEvent.h"
#include "MidiEvents/ChannelEvents/MidiPitchBendEvent.h"

// Sysex events
#include "MidiEvents/SysexEvents/MidiSysexEvent.h"

// Meta Events
#include "MidiEvents/MetaEvents/MidiMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiSequenceNumberMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiTextMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiCopyRightNoticeMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiSequenceTrackNameMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiInstrumentNameMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiLyricsMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiMarkerMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiCuePointMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiChannelPrefixMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiEndOfTrackMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiSetTempoMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiSMPTEOffsetMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiTimeSignatureMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiKeySignatureMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiSequencerSpecificMetaEvent.h"
#include "MidiEvents/MetaEvents/MidiUnknownMetaEvent.h"

static const char* TRACK_HEADER_DATA = "MTrk";

class MidiTrackChunk
{
public:
	static const uint32_t HEADER_SIZE = 4; // MTrk

public:
	char chunk_id[5];
	uint32_t chunk_size;
	uint8_t* data;

public:
	MidiTrackChunk(uint32_t track_number)
	{
		m_track_number = track_number;
	}

	~MidiTrackChunk()
	{
		for (unsigned int i = 0; i < m_events.size(); ++i)
		{
			delete m_events[i];
		}
	}

public:
	bool parse_header(uint8_t* data)
	{
		memcpy(chunk_id, data, MidiTrackChunk::HEADER_SIZE);
		chunk_id[MidiTrackChunk::HEADER_SIZE] = 0;
		return (strcmp(TRACK_HEADER_DATA, chunk_id) == 0);
	}

	bool parse()
	{
		uint8_t* file_pos = data;
		uint8_t last_status_byte = 0;
		bool running_status = false;
		bool save_status_byte = true;
		TICKS song_time = 0;
		while (static_cast<size_t>(file_pos - data) < chunk_size)
		{
			uint32_t bytes_read;
			TICKS delta_time = Midi::parse_var_length(file_pos, bytes_read);
			song_time += delta_time;

			file_pos += bytes_read;

			uint8_t status = *file_pos; // parse_status_byte() ?

			// Running status
			if ( (status & 0x80) == 0)
			{
				status = last_status_byte;
				running_status = true;
				save_status_byte = false;
				--bytes_read;
			}
			else
			{
				running_status = false;
				save_status_byte = true;
				++file_pos;
			}

			if (status == MidiEvent::SYSEX)
			{
				running_status = false;
				uint32_t bytesread = parse_sysex_event(delta_time, file_pos, song_time);
				file_pos += bytesread;
			}
			else if (status == MidiEvent::META)
			{
				running_status = false;
				uint32_t bytesread = parse_meta_event(delta_time, file_pos, song_time);
				file_pos += bytesread;
			}
			else
			{
				uint8_t event_type = status & 0xF0;
				uint8_t channel = status & 0x0F;

				MidiEvent* e = nullptr;

				switch(event_type)
				{
					case MidiEvent::NOTE_OFF:			//= 0x80,
						e = new MidiNoteOffEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::NOTE_ON:			//= 0x90,
						e = new MidiNoteOnEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::NOTE_AFTERTOUCH:	//= 0xA0,
						e = new MidiAfterTouchEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::CONTROLLER:			//= 0xB0,
						e = new MidiControllerEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::PROGRAM_CHANGE:		//= 0xC0,
						e = new MidiProgramChangeEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::CHANNEL_AFTERTOUCH:	//= 0xD0,
						e = new MidiChannelAfterTouchEvent(delta_time, file_pos, channel, song_time);
						break;

					case MidiEvent::PITCH_BEND:			//= 0xE0,
						e = new MidiPitchBendEvent(delta_time, file_pos, channel, song_time);
						break;
				};
				m_events.push_back(e);
				file_pos += e->message_length();
			}

			if (save_status_byte)
				last_status_byte = status;
		}
		return true;
	}
		
	std::vector<MidiEvent*>& events()
	{
		return m_events;
	}

	const std::string& track_name() const
	{
		return m_track_name;
	}

	uint32_t track_number() const
	{
		return m_track_number;
	}

private:
	uint32_t parse_sysex_event(TICKS delta_time, uint8_t* file_pos, TICKS song_time)
	{
		uint32_t bytes_read;
		uint32_t event_size = Midi::parse_var_length(file_pos, bytes_read);
		file_pos += bytes_read;
		bytes_read += event_size;
		MidiSysexEvent* e = new MidiSysexEvent(delta_time, file_pos, event_size, song_time);
		m_events.push_back(e);
		return bytes_read;
	}

	uint32_t parse_meta_event(TICKS delta_time, uint8_t* file_pos, TICKS song_time)
	{
		uint32_t bytes_read = 1;
		uint8_t meta_event_type = *file_pos;
		bytes_read++; file_pos++;
		MidiMetaEvent* e = nullptr;
		switch (meta_event_type)
		{
			case MidiMetaEvent::SEQUENCE_NUMBER:		// 0x00
				e = new MidiSequenceNumberMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::TEXT:					// 0x01
				e = new MidiTextMetaEvent(delta_time, file_pos, song_time);
				break;


			case MidiMetaEvent::COPYRIGHT_NOTICE:		// 0x02
				e = new MidiCopyrightNoticeMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::SEQUENCE_TRACK_NAME:	// 0x03
				e = new MidiSequenceTrackNameMetaEvent(delta_time, file_pos, song_time);
				m_track_name = static_cast<MidiSequenceTrackNameMetaEvent*>(e)->track_name();
				break;

			case MidiMetaEvent::INSTRUMENT_NAME:		// 0x04
				e = new MidiInstrumentNameMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::LYRICS:					// 0x05
				e = new MidiLyricsMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::MARKER:					// 0x06
				e = new MidiMarkerMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::CUE_POINT:				// 0x07
				e = new MidiCuePointMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::MIDI_CHANNEL_PREFIX:	// 0x20
				e = new MidiChannelPrefixMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::END_OF_TRACK:			// 0x2F
				e = new MidiEndOfTrackMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::SET_TEMPO:				// 0x51
				e = new MidiSetTempoMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::SMPTE_OFFSET:			// 0x54
				e = new MidiSMPTEOffsetMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::TIME_SIGNATURE:			// 0x58
				e = new MidiTimeSignatureMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::KEY_SIGNATURE:			// 0x59
				e = new MidiKeySignatureMetaEvent(delta_time, file_pos, song_time);
				break;

			case MidiMetaEvent::SEQUENCER_SPECIFIC:			// 0x7F
				e = new MidiSequencerSpecificMetaEvent(delta_time, file_pos, song_time);
				break;

			default:
				e = new MidiUnknownMetaEvent(delta_time, file_pos, song_time, meta_event_type);
				break;
		}
		bytes_read += e->message_length();
		m_events.push_back(e);
		return bytes_read;
	}

private:
	uint32_t m_track_number;
	std::string m_track_name;
	std::vector<MidiEvent*> m_events;

};