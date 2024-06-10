#pragma once

#include "MidiMetaEvent.h"

class MidiLyricsMetaEvent : public MidiMetaEvent
{
public:
	MidiLyricsMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::LYRICS)
	{
		m_lyrics = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) META EVENT : LYRICS, string = %s\n", song_time(), real_time(), m_lyrics.c_str());
		return std::string(buffer);
	}

private:
	std::string m_lyrics;
};