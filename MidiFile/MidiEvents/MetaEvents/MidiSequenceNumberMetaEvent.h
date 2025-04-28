#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiSequenceNumberMetaEvent : public MidiMetaEvent
{
public:
	MidiSequenceNumberMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SEQUENCE_NUMBER)
	{
		if (delta_time != 0)
		{
			// error
		}
		m_sequence_number = Midi::parse_uint16(data);
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : SEQUENCE NUMBER, sequence nr = " << m_sequence_number << "\n";
		return std::string(ss.str());
	}

private:
	uint16_t m_sequence_number;
};
