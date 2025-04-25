#pragma once

#include "Midi.h"
#include "MidiFile.h"

static const char* MIDI_HEADER_DATA = "MThd";

class MidiHeaderChunk
{
public:
	static const int HEADER_PARSE_SIZE = 0x30; // Nice assumption that Mthd has to be found within the first 48 bytes (RIFF metaheader)
	static const uint32_t SIZE = 14;
	static const int MIN_NUM_TRACKS = 1;
	static const int MAX_NUM_TRACKS = 65535;
	static const int FORMAT_TYPE = 2;

	enum TimeDivisionType
	{
		TICKS_PER_BEAT,
		FRAMES_PER_SECOND
	};

public:
	MidiHeaderChunk()
	: m_valid(false)
	{
	}

public:
	int32_t header_location(uint8_t* data)
	{
		std::string header = std::string((const char*) data, HEADER_PARSE_SIZE);
		
		size_t header_location = header.find(MIDI_HEADER_DATA);
		if (header_location == std::string::npos)
		{
			m_valid = false;
			return -1;
		}

		size_t data_pos = header_location + strlen(MIDI_HEADER_DATA);

		chunk_size = Midi::parse_uint32(data+data_pos);
		data_pos += sizeof(uint32_t);

		format_type = Midi::parse_uint16(data+data_pos);
		data_pos += sizeof(uint16_t);

		number_of_tracks = Midi::parse_uint16(data+data_pos);
		data_pos += sizeof(uint16_t);

		time_division = Midi::parse_uint16(data+data_pos);
		data_pos += sizeof(uint16_t);

		// TODO add logging someday
		if (format_type > FORMAT_TYPE || number_of_tracks < MIN_NUM_TRACKS || number_of_tracks > MAX_NUM_TRACKS)
		{
			m_valid = false;
			return -1;
		}

		return static_cast<int32_t>(header_location);
	}

public:
	uint32_t chunk_size;
	uint16_t format_type;
	uint16_t number_of_tracks;
	uint16_t time_division;

	uint16_t get_format_type() const
	{
		return format_type;
	}

	uint16_t get_num_tracks() const
	{
		return number_of_tracks;
	}

	uint16_t get_time_division() const
	{
		return time_division & 0x7FFF;
	}

	TimeDivisionType get_time_division_type() const
	{
		if ((time_division & 0x8000) == 0)
			return TICKS_PER_BEAT;

		return FRAMES_PER_SECOND;
	}

	bool is_valid() const
	{
		return m_valid;
	}

private:
	bool m_valid;
};
