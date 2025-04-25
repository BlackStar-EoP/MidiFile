#pragma once

#include "../MidiEvent.h"

class MidiChannelEvent : public MidiEvent
{
public:
	MidiChannelEvent(MIDI_EVENT event_type, uint8_t channel, TICKS delta_time, TICKS song_time)
	: MidiEvent(event_type, delta_time, song_time)
	, m_channel(channel)
	{
	}

	uint8_t channel() const
	{
		return m_channel;
	}

	void set_channel(uint8_t channel)
	{
		if (channel < 16)
			m_channel = channel;
	}

private:
	uint8_t m_channel;
};
