#pragma once

#include "../MidiEvent.h"

class MidiSysexEvent : public MidiEvent
{
public:
	MidiSysexEvent(TICKS delta_time, uint8_t* data, uint32_t event_length, TICKS song_time)
	: MidiEvent(MidiEvent::SYSEX, delta_time, song_time)
	{
		m_message_length = event_length;
		copy_message(data, event_length);
	}

	~MidiSysexEvent()
	{
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) SYSEX EVENT BIG TODO\n", song_time(), real_time());
		return std::string(buffer);
	}
};
