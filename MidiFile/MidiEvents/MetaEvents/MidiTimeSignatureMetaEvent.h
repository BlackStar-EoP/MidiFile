#pragma once

#include "MidiMetaEvent.h"

#include <sstream>

class MidiTimeSignatureMetaEvent : public MidiMetaEvent
{
	/*
		Time Signature
		This meta event is used to set a sequences time signature. 
		The time signature defined with 4 bytes, a numerator, a denominator, a metronome pulse and number of 32nd notes per MIDI quarter-note.
		The numerator is specified as a literal value, but the denominator is specified as (get ready) 
		the value to which the power of 2 must be raised to equal the number of subdivisions per whole note. 
		For example, a value of 0 means a whole note because 2 to the power of 0 is 1 (whole note), 
		a value of 1 means a half-note because 2 to the power of 1 is 2 (half-note), and so on. 
		The metronome pulse specifies how often the metronome should click in terms of the number of clock signals per click, 
		which come at a rate of 24 per quarter-note. For example, a value of 24 would mean to click once every quarter-note (beat) and 
		a value of 48 would mean to click once every half-note (2 beats). And finally, the fourth uint8_t specifies the number of 32nd notes per 24 MIDI clock signals. 
		This value is usually 8 because there are usually 8 32nd notes in a quarter-note. At least one Time Signature Event should appear in the first track chunk 
		(or all track chunks in a Type 2 file) before any non-zero delta time events. If one is not specified 4/4, 24, 8 should be assumed.
	*/
public:
	MidiTimeSignatureMetaEvent(TICKS delta_time, uint8_t* data, TICKS song_time)
	: MidiMetaEvent(delta_time, data, song_time, MidiMetaEvent::TIME_SIGNATURE)
	{
		++data;
		m_numerator = data[0];
		m_denominator = data[1];
		m_metronome = data[2];
		m_32nds = data[3];
	}

	std::string to_string() override
	{
		std::stringstream ss;
		ss << song_time() << "(" << real_time() << ") META EVENT : TIME SIGNATURE " << m_numerator << "/" << pow(2, m_denominator) << " metronome = " << m_metronome << ", 32nds = " << m_32nds << "\n";
		return std::string(ss.str());
	}

private:
	uint32_t pow(uint32_t base, uint32_t exp)
	{
		uint32_t result = 1;
		for (uint32_t i = 0; i < exp; ++i)
		{
			result *= base;
		}
		return result;
	}

private:
		uint8_t m_numerator;
		uint8_t m_denominator;
		uint8_t m_metronome;
		uint8_t m_32nds;
};
