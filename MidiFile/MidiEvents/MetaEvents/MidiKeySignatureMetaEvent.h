#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

/* Todo add enum ? */
class MidiKeySignatureMetaEvent : public MidiMetaEvent
{
public:
	MidiKeySignatureMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::KEY_SIGNATURE)
	{
		m_key = data[0];
		m_scale = data[1];
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : KEY SIGNATURE key = " << m_key << ", scale = " << m_scale << "\n";
		return std::string(ss.str());
	}

private:
		uint8_t m_key;
		uint8_t m_scale;
};
