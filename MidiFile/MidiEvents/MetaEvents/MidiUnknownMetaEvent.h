#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiUnknownMetaEvent : public MidiMetaEvent
{
public:
	MidiUnknownMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time, uint8_t meta_event_type)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::UNKNOWN)
	, m_unknown_meta_event_type(meta_event_type)
	{
		
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : UNKNOWN! nr = " << m_unknown_meta_event_type << "\n";
		return std::string(ss.str());
	}

private:
	uint8_t m_unknown_meta_event_type;

};