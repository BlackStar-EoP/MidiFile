#pragma once

#include "MidiMetaEvent.h"

class MidiSMPTEOffsetMetaEvent : public MidiMetaEvent
{
public:
	MidiSMPTEOffsetMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SMPTE_OFFSET)
	{
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : SMPTE OFFSET\n", song_time(), real_time());
		return std::string(buffer);
	}
};