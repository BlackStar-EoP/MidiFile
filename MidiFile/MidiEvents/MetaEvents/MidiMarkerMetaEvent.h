#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiMarkerMetaEvent : public MidiMetaEvent
{
public:
	MidiMarkerMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::MARKER)
	{
		m_marker = parse_string();
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : MARKER, string = " << m_marker << "\n";
		return ss.str();
	}

private:
	std::string m_marker;
};