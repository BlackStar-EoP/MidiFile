#pragma once

#include "MidiChannelEvent.h"

class MidiControllerEvent : public MidiChannelEvent
{
public:
	enum CONTROLLER_TYPES
	{
		/*	
		0 (0x00)	Bank Select
		1 (0x01)	Modulation
		2 (0x02)	Breath Controller
		4 (0x04)	Foot Controller
		5 (0x05)	Portamento Time
		6 (0x06)	Data Entry (MSB)
		7 (0x07)	Main Volume
		8 (0x08)	Balance
		10 (0x0A)	Pan
		11 (0x0B)	Expression Controller
		12 (0x0C)	Effect Control 1
		13 (0x0D)	Effect Control 2
		16-19 (0x10-0x13)	General-Purpose Controllers 1-4
		32-63 (0x20-0x3F)	LSB for controllers 0-31
		64 (0x40)	Damper pedal (sustain)
		65 (0x41)	Portamento
		66 (0x42)	Sostenuto
		67 (0x43)	Soft Pedal
		68 (0x44)	Legato Footswitch
		69 (0x45)	Hold 2
		70 (0x46)	Sound Controller 1 (default: Timber Variation)
		71 (0x47)	Sound Controller 2 (default: Timber/Harmonic Content)
		72 (0x48)	Sound Controller 3 (default: Release Time)
		73 (0x49)	Sound Controller 4 (default: Attack Time)
		74-79 (0x4A-0x4F)	Sound Controller 6-10
		80-83 (0x50-0x53)	General-Purpose Controllers 5-8
		84 (0x54)	Portamento Control
		91 (0x5B)	Effects 1 Depth (formerly External Effects Depth)
		92 (0x5C)	Effects 2 Depth (formerly Tremolo Depth)
		93 (0x5D)	Effects 3 Depth (formerly Chorus Depth)
		94 (0x5E)	Effects 4 Depth (formerly Celeste Detune)
		95 (0x5F)	Effects 5 Depth (formerly Phaser Depth)
		96 (0x60)	Data Increment
		97 (0x61)	Data Decrement
		98 (0x62)	Non-Registered Parameter Number (LSB)
		99 (0x63)	Non-Registered Parameter Number (MSB)
		100 (0x64)	Registered Parameter Number (LSB)
		101 (0x65)	Registered Parameter Number (MSB)
		121-127 (0x79-0x7F)	Mode Messages*/
	};


public:
	MidiControllerEvent(TICKS delta_time, uint8_t* data, uint8_t channel, TICKS song_time)
	: MidiChannelEvent(MidiEvent::CONTROLLER, channel, delta_time, song_time)
	{
		m_controller_type = data[0];
		m_value = data[1];
		m_message_length = 2;
	}

public:
	uint8_t controller_type() const
	{
		return m_controller_type;
	}

	uint8_t value() const
	{
		return m_value;
	}

	virtual std::string to_string()
	{
		char buffer[256];
		sprintf_s(buffer, "%u(%f) CONTROLLER EVENT , controller type = %u, value = %u\n", song_time(), real_time(), m_controller_type, m_value);
		return std::string(buffer);
	}

private:
	uint8_t m_controller_type;
	uint8_t m_value;
};