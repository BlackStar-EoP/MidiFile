#pragma once

#include "MidiChannelEvent.h"

class MidiChannelAfterTouchEvent : public MidiChannelEvent
{
public:
	MidiChannelAfterTouchEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::CHANNEL_AFTERTOUCH, channel, delta_time, song_time)
	{
		m_amount = data[0];
		m_message_length = 1;
	}

public:
	uint8_t amount() const
	{
		return m_amount;
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) CHANNEL AFTERTOUCH EVENT amount = %u\n", song_time(), real_time(), m_amount);
		return std::string(buffer);
	}

private:
	uint8_t m_amount;

};
