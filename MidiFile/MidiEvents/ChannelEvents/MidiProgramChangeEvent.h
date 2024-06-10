#pragma once

#include "MidiChannelEvent.h"

static const uint8_t MAX_CHANNEL = 16;

class MidiProgramChangeEvent : public MidiChannelEvent
{
public:
	MidiProgramChangeEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::PROGRAM_CHANGE, channel, delta_time, song_time)
	{
		m_program_number = data[0];
		m_message_length = 1;
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
		char buffer[256];
		sprintf(buffer, "%u(%f) PROGRAM CHANGE EVENT , program nr = %u\n", song_time(), real_time(), m_program_number);
		return std::string(buffer);
	}

private:
	uint8_t m_program_number;
};