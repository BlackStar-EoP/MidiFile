#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiSMPTEOffsetMetaEvent : public MidiMetaEvent
{
public:
	MidiSMPTEOffsetMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SMPTE_OFFSET)
	{
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " SMPTE OFFSET\n";
		return ss.str();
	}
};