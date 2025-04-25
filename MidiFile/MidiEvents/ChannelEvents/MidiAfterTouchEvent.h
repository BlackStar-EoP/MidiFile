#pragma once

#include "MidiChannelEvent.h"

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
		char buffer[256];
		sprintf_s(buffer, "%u(%f) AFTERTOUCH EVENT , note nr = %u, amount = %u\n", song_time(), real_time(), m_note_number, m_amount);
		return std::string(buffer);
	}

private:
	uint8_t m_note_number;
	uint8_t m_amount;

};