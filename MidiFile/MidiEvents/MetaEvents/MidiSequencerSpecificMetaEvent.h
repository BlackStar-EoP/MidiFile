#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiSequencerSpecificMetaEvent : public MidiMetaEvent
{
public:
	MidiSequencerSpecificMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SEQUENCER_SPECIFIC)
	{
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : SEQUENCER SPECIFIC BIG todo\n";
		return ss.str();
	}
};