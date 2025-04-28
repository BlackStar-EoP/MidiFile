#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiLyricsMetaEvent : public MidiMetaEvent
{
public:
	MidiLyricsMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::LYRICS)
	{
		m_lyrics = Midi::parse_string(data + 1, m_message_length);
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : LYRICS, string = \"" << m_lyrics << "\"\n";
		return std::string(ss.str());
	}

private:
	std::string m_lyrics;
};