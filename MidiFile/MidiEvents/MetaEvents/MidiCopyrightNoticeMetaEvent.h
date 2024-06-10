#pragma once

#include "MidiMetaEvent.h"

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
		m_copyright_notice = Midi::parse_string(data + 1, m_message_length);
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf(buffer, "%u(%f) META EVENT : COPYRIGHT NOTICE, string = %s\n", song_time(), real_time(), m_copyright_notice.c_str());
		return std::string(buffer);
	}

private:
	std::string m_copyright_notice;
};