#pragma once

#include "MidiMetaEvent.h"

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
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : CUE POINT, string = %s\n", song_time(), real_time(), m_cue_point.c_str());
		return std::string(buffer);
	}

private:
	std::string m_cue_point;

};
