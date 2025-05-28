#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiInstrumentNameMetaEvent : public MidiMetaEvent
{
public:
	MidiInstrumentNameMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::INSTRUMENT_NAME)
	{
		m_instrument_name = parse_string();
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : INSTRUMENT NAME, string = " << m_instrument_name << "\n";
		return ss.str();
	}

private:
	std::string m_instrument_name;
};