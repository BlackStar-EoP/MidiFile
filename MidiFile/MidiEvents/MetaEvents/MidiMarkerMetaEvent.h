#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiMarkerMetaEvent : public MidiMetaEvent
{
public:
	MidiMarkerMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::MARKER)
	{
		m_marker = Midi::parse_string(data + 1, m_message_length);
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : MARKER, string = \"" << m_marker << "\"\n";
		return std::string(ss.str());
	}

private:
	std::string m_marker;
};