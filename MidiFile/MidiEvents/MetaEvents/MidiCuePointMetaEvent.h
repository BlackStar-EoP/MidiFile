#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiCuePointMetaEvent : public MidiMetaEvent
{
public:
	MidiCuePointMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::CUE_POINT)
	{
		m_cue_point = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : CUE POINT, string = " << m_cue_point << "\n";
		return ss.str();
	}

private:
	std::string m_cue_point;

};
