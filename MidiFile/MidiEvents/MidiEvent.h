#pragma once

#include "../Midi.h"

class MidiEvent
{
public:
	enum MIDI_EVENT
	{
		NOTE_OFF			= 0x80,
		NOTE_ON				= 0x90,
		NOTE_AFTERTOUCH		= 0xA0,
		CONTROLLER			= 0xB0,
		PROGRAM_CHANGE		= 0xC0,
		CHANNEL_AFTERTOUCH  = 0xD0,
		PITCH_BEND			= 0xE0,
		SYSEX				= 0xF0,
		META				= 0xFF
	};

public:
	MidiEvent(MIDI_EVENT event_type, TICKS delta_time, TICKS song_time)
    : m_message_length(0)
	, m_delta_time(delta_time)
	, m_song_time(song_time)
    , m_real_time(0.0f)
    , m_event_type(event_type)
	, m_message(nullptr)
	{
	}

	virtual ~MidiEvent()
	{
		delete[] m_message;
	}

	const uint8_t* message() const
	{
		return m_message;
	}

	uint32_t message_length() const
	{
		return m_message_length;
	}

	MIDI_EVENT event_type() const
	{
		return m_event_type;
	}

	TICKS delta_time() const
	{
		return m_delta_time;
	}

	TICKS song_time() const
	{
		return m_song_time;
	}

	float real_time() const
	{
		return m_real_time;
	}

	void set_real_time(float real_time)
	{
		m_real_time = real_time;
	}

	virtual std::string to_string() = 0;

protected:
	uint32_t m_message_length;
	
	void copy_message(const uint8_t* data, uint32_t length)
	{
		m_message = new uint8_t[length];
		memcpy(m_message, data, length);
	}

	void calculate_real_time()
	{
		m_real_time = 1.0f;
	}

private:
	TICKS m_delta_time;
	TICKS m_song_time;
	float m_real_time;
	MIDI_EVENT m_event_type;
	uint8_t* m_message;
};