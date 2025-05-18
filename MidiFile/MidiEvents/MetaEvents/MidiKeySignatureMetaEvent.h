#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiKeySignatureMetaEvent : public MidiMetaEvent
{
public:
	MidiKeySignatureMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::KEY_SIGNATURE)
	{
		m_key = data[0u];
		m_scale = data[1u];
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : KEY SIGNATURE todo\n";
		return ss.str();
	}

private:
		uint8_t m_key;
		uint8_t m_scale;
};
