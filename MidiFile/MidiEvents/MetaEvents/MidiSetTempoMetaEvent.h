#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiSetTempoMetaEvent : public MidiMetaEvent
{
public:
	MidiSetTempoMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SET_TEMPO)
	{
		++data;
		m_microseconds_per_quarter_note = data[0] << 16 | data[1] << 8 | data[2];
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " SET TEMPO, microseconds per quarter note = " << m_microseconds_per_quarter_note << "\n";
		return ss.str();
	}

	uint32_t microseconds_per_quarter_note() const
	{
		return m_microseconds_per_quarter_note;
	}

private:
	uint32_t m_microseconds_per_quarter_note;
};