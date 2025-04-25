#pragma once

#include "MidiMetaEvent.h"

class MidiSequencerSpecificMetaEvent : public MidiMetaEvent
{
public:
	MidiSequencerSpecificMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SEQUENCER_SPECIFIC)
	{
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : SEQUENCER SPECIFIC BIG todo\n", song_time(), real_time());
		return std::string(buffer);
	}
};