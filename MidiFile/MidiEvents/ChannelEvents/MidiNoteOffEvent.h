#pragma once

#include "MidiChannelEvent.h"

#include <sstream>

class MidiNoteOffEvent : public MidiChannelEvent
{
public:
	MidiNoteOffEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::NOTE_OFF, channel, delta_time, song_time)
	{
		m_note_number = data[0];
		m_velocity = data[1];
		m_message_length = 2;
	}

public:
	uint8_t note_number() const
	{
		return m_note_number;
	}

	uint8_t velocity() const
	{
		return m_velocity;
	}
	
	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " NOTE OFF EVENT , note nr = " << m_note_number << ", velocity = " << m_velocity << ", channel = " << channel() << "\n";
		return ss.str();
	}

private:
	uint8_t m_note_number;
	uint8_t m_velocity;
};