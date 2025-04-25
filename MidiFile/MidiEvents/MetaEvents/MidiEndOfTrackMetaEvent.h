#pragma once

#include "MidiMetaEvent.h"

class MidiEndOfTrackMetaEvent : public MidiMetaEvent
{
public:
	MidiEndOfTrackMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::END_OF_TRACK)
	{
		m_channel = *data;
		m_message_length = 0;
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) META EVENT : END OF TRACK, channel= %u\n", song_time(), real_time(), m_channel);
		return std::string(buffer);
	}

private:
	uint8_t m_channel;
};
