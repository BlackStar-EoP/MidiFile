#pragma once

#include "MidiChannelEvent.h"

#include <sstream>

class MidiNoteOnEvent : public MidiChannelEvent
{
public:
	MidiNoteOnEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::NOTE_ON, channel, delta_time, song_time)
	{
		m_note_number = data[0];
		m_velocity = data[1];
		m_message_length= 2;
		m_channel = channel;
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

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") NOTE ON EVENT , note nr = " << m_note_number << ", velocity = " << m_velocity << ", channel = " << channel() << "\n";
		return std::string(ss.str());
	}

private:
	uint8_t m_note_number;
	uint8_t m_velocity;
	uint8_t m_channel;
};