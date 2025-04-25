#pragma once

#include "MidiMetaEvent.h"

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

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : SEQUENCE NUMBER, sequence nr = %u\n", song_time(), real_time(), m_sequence_number);
		return std::string(buffer);
	}

private:
	uint16_t m_sequence_number;
};
