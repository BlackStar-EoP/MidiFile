#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiCopyrightNoticeMetaEvent : public MidiMetaEvent
{
public:
	MidiCopyrightNoticeMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::COPYRIGHT_NOTICE)
	{
		//if (track_chunk != 0) error
		//if current_time != 0) error
		if (delta_time != 0)
		{
			// error
		}
		m_copyright_notice = parse_string();
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : COPYRIGHT NOTICE, string = " << m_copyright_notice << "\n";
		return ss.str();
	}

private:
	std::string m_copyright_notice;
};