#pragma once

#include "MidiMetaEvent.h"

class MidiKeySignatureMetaEvent : public MidiMetaEvent
{
public:
	MidiKeySignatureMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::KEY_SIGNATURE)
	{
		m_key = data[0];
		m_scale = data[1];
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) META EVENT : KEY SIGNATURE todo\n", song_time(), real_time());
		return std::string(buffer);
	}

private:
		uint8_t m_key;
		uint8_t m_scale;
};
