#pragma once

#include "MidiChannelEvent.h"

#include <sstream>

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
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ")" << " CHANNEL AFTERTOUCH EVENT amount = " << m_amount << "\n";
		return ss.str();
	}

private:
	uint8_t m_amount;

};
