#pragma once

#include "MidiMetaEvent.h"

class MidiInstrumentNameMetaEvent : public MidiMetaEvent
{
public:
	MidiInstrumentNameMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::INSTRUMENT_NAME)
	{
		m_instrument_name = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : INSTRUMENT NAME, string = %s\n", song_time(), real_time(), m_instrument_name.c_str());
		return std::string(buffer);
	}

private:
	std::string m_instrument_name;
};