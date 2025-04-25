#pragma once

#include "MidiChannelEvent.h"

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

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) PITCH BEND EVENT value = %u\n", song_time(), real_time(), m_value);
		return std::string(buffer);
	}

private:
	uint16_t m_value;
};