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

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : SMPTE OFFSET\n";
		return std::string(ss.str());
	}
};