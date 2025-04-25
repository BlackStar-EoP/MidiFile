#pragma once

#include "MidiMetaEvent.h"

class MidiMarkerMetaEvent : public MidiMetaEvent
{
public:
	MidiMarkerMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::MARKER)
	{
		m_marker = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : MARKER, string = %s\n", song_time(), real_time(), m_marker.c_str());
		return std::string(buffer);
	}

private:
	std::string m_marker;
};