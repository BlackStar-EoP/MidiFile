#pragma once

#include "MidiChannelEvent.h"

#include <sstream>

class MidiPitchBendEvent : public MidiChannelEvent
{
public:
	MidiPitchBendEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::PITCH_BEND, channel, delta_time, song_time)
	{
		m_value = (data[0] << 7) | data[1];
		m_message_length = 2;
	}

public:
	uint16_t value() const
	{
		return m_value;
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") PITCH BEND EVENT value = " << m_value << "\n";
		return std::string(ss.str());
	}

private:
	uint16_t m_value;
};