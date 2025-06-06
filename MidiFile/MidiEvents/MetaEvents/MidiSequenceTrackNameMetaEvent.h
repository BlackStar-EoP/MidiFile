#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiSequenceTrackNameMetaEvent : public MidiMetaEvent
{
public:
	MidiSequenceTrackNameMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
		: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::SEQUENCE_TRACK_NAME)
	{
		m_track_name = parse_string();
	}

	virtual std::string to_string()
	{
		std::stringstream ss;

		ss << song_time() << "(" << real_time() << ")" << " META EVENT : TRACK NAME, string = " << m_track_name << "\n";
		return ss.str();
	}

	const std::string& track_name() const
	{
		return m_track_name;
	}

private:
	std::string m_track_name;
};