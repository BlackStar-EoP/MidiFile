#pragma once

#include "MidiMetaEvent.h"

class MidiTextMetaEvent : public MidiMetaEvent
{
public:
	MidiTextMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::TEXT)
	{
		m_text = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) META EVENT : TEXT EVENT, string = %s\n", song_time(), real_time(), m_text.c_str());
		return std::string(buffer);
	}

private:
	std::string m_text;
};