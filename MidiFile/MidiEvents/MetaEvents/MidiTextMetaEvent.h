#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiTextMetaEvent : public MidiMetaEvent
{
public:
	MidiTextMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::TEXT)
	{
		m_text = Midi::parse_string(data + 1, m_message_length);
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : TEXT EVENT, string = \"" << m_text << "\"\n";
		return std::string(ss.str());
	}

private:
	std::string m_text;
};