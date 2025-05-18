#pragma once

#include "MidiChannelEvent.h"

#include <sstream>

static const uint8_t MAX_CHANNEL = 16u;

class MidiProgramChangeEvent : public MidiChannelEvent
{
public:
	MidiProgramChangeEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::PROGRAM_CHANGE, channel, delta_time, song_time)
	{
		m_program_number = data[0u];
		m_message_length = 1u;
	}

public:
	uint8_t program_number() const
	{
		return m_program_number;
	}

	void set_program_number(uint8_t program_number)
	{
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " PROGRAM CHANGE EVENT , program nr = " << m_program_number << "\n";
		return ss.str();
	}

private:
	uint8_t m_program_number;
};