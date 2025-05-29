#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiTextMetaEvent : public MidiMetaEvent
{
public:
	MidiTextMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::TEXT)
	{
        m_text = parse_string();
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : TEXT EVENT, string = " << m_text << "\n";
		return ss.str();
	}

private:
	std::string m_text;
};