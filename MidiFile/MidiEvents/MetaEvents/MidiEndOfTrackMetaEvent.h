#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiEndOfTrackMetaEvent : public MidiMetaEvent
{
public:
	MidiEndOfTrackMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::END_OF_TRACK)
	{
		m_channel = *data;
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : END OF TRACK, channel = " << m_channel << "\n";
		return ss.str();
	}

private:
	uint8_t m_channel;
};