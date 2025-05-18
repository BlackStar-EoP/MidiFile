#pragma once

#include "MidiChannelEvent.h"
#include <sstream>

class MidiAfterTouchEvent : public MidiChannelEvent
{
public:
	MidiAfterTouchEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::NOTE_AFTERTOUCH, channel, delta_time, song_time)
	{
		m_note_number = data[0];
		m_amount = data[1];
		m_message_length = 2;
	}

public:
	uint8_t note_number() const
	{
		return m_note_number;
	}

	uint8_t amount() const
	{
		return m_amount;
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " AFTERTOUCH EVENT , note nr = " << m_note_number << ", amount = " << m_amount << "\n";
		return ss.str();
	}

private:
	uint8_t m_note_number;
	uint8_t m_amount;

};