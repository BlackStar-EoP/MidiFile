#pragma once

#include "MidiMetaEvent.h"

class MidiChannelPrefixMetaEvent : public MidiMetaEvent
{
public:
	MidiChannelPrefixMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::MIDI_CHANNEL_PREFIX)
	{
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : CHANNEL PREFIX\n", song_time(), real_time());
		return std::string(buffer);
	}
};