#pragma once

#include "MidiMetaEvent.h"

class MidiSequenceTrackNameMetaEvent : public MidiMetaEvent
{
public:
	MidiSequenceTrackNameMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
		: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SEQUENCE_TRACK_NAME)
	{
		m_track_name = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) META EVENT : TRACK NAME, string = %s\n", song_time(), real_time(), m_track_name.c_str());
		return std::string(buffer);
	}

	const std::string& track_name() const
	{
		return m_track_name;
	}

private:
	std::string m_track_name;
};