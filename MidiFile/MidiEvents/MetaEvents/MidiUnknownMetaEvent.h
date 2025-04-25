#pragma once

#include "MidiMetaEvent.h"

class MidiUnknownMetaEvent : public MidiMetaEvent
{
public:
	MidiUnknownMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time, uint8_t meta_event_type)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::UNKNOWN)
	, m_unknown_meta_event_type(meta_event_type)
	{
		
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : UNKNOWN! (nr=%u)\n", song_time(), real_time(), m_unknown_meta_event_type);
		return std::string(buffer);
	}

private:
	uint8_t m_unknown_meta_event_type;

};