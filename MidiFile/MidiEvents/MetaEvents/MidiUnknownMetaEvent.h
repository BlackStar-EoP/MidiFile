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

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : UNKNOWN nr = " << m_unknown_meta_event_type << "\n";
		return ss.str();
	}

private:
	uint8_t m_unknown_meta_event_type;

};