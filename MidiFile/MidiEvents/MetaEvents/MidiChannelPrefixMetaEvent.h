#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiChannelPrefixMetaEvent : public MidiMetaEvent
{
public:
	MidiChannelPrefixMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::MIDI_CHANNEL_PREFIX)
	{
	}

	virtual std::string to_string()
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : CHANNEL PREFIX\n";
		return std::string(ss.str());
	}
};