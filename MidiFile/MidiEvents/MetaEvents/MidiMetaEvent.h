#pragma once

#include "../MidiEvent.h"

class MidiMetaEvent : public MidiEvent
{
public:

	enum META_EVENT_TYPE
	{
		SEQUENCE_NUMBER			= 0x00,
		TEXT					= 0x01,
		COPYRIGHT_NOTICE		= 0x02,
		SEQUENCE_TRACK_NAME		= 0x03,
		INSTRUMENT_NAME			= 0x04,
		LYRICS					= 0x05,
		MARKER					= 0x06,
		CUE_POINT				= 0x07,
		MIDI_CHANNEL_PREFIX		= 0x20,
		END_OF_TRACK			= 0x2F,
		SET_TEMPO				= 0x51,
		SMPTE_OFFSET			= 0x54,
		TIME_SIGNATURE			= 0x58,
		KEY_SIGNATURE			= 0x59,
		SEQUENCER_SPECIFIC		= 0x7F,
		UNKNOWN					= 0xFF
	};

	//	Meta Event	Type	Length      	Data
	// 255 (0xFF)	0-255	variable-length	type specific
	MidiMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time, META_EVENT_TYPE meta_event_type)
	: MidiEvent(MidiEvent::META, delta_time, song_time)
	, m_data(data)
	, m_meta_event_type(meta_event_type)
	{
		uint32_t bytes_read;
		m_message_length = Midi::parse_var_length(data, bytes_read);
		m_data += bytes_read;
	}

	META_EVENT_TYPE meta_event_type() const
	{
		return m_meta_event_type;
	}

	virtual std::string to_string() = 0;
protected:
	uint8_t* m_data;

private:
	META_EVENT_TYPE m_meta_event_type;
};