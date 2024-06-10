#pragma once

#include <string>
#include <stdint.h>

typedef uint32_t TICKS;

#define TRACE_WARNING(...)
#define TRACE_ERROR(...)

namespace Midi
{
	static const uint32_t MICROSECONDS_PER_MINUTE = 60000000;

	static uint32_t parse_uint32(uint8_t* data)
	{
		return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
	}

	static uint16_t parse_uint16(uint8_t* data)
	{
		return data[0] << 8 | data[1];
	}

	static uint32_t parse_var_length(uint8_t* data, uint32_t& byte_count)
	{
		byte_count = 0;
		uint32_t value = 0;
		bool has_next = false;
		do
		{
			value <<= 7;
			value |= (data[byte_count] & 0x7F);
			has_next = data[byte_count] & 0x80;
			++byte_count;
		}
		while(has_next);
		return value;
	}

	static std::string parse_string(uint8_t* data, uint32_t string_length)
	{
		return std::string((const char*) data, (size_t) string_length);
	}
}

namespace Midi
{
	static const uint8_t NUM_INSTRUMENTS = 128;

	static std::string instruments[NUM_INSTRUMENTS] = 
	{
		// Piano
		"Acoustic Grand Piano", // = 0
		"Bright Acoustic Piano", // = 1
		"Electric Grand Piano", // = 2
		"Honky-tonk Piano", // = 3
		"Electric Piano 1", // = 4
		"Electric Piano 2", // = 5
		"Harpsichord", // = 6
		"Clavinet", // = 7
		// Chromatic Percussion
		"Celesta", // = 8
		"Glockenspiel", // = 9
		"Music Box", // = 10
		"Vibraphone", // = 11
		"Marimba", // = 12
		"Xylophone", // = 13
		"Tubular Bells", // = 14
		"Dulcimer", // = 15
		// Organ
		"Drawbar Organ", // = 16
		"Percussive Organ", // = 17
		"Rock Organ", // = 18
		"Church Organ", // = 19
		"Reed Organ", // = 20
		"Accordion", // = 21
		"Harmonica", // = 22
		"Tango Accordion", // = 23
		// Guitar
		"Acoustic Guitar (nylon)", // = 24
		"Acoustic Guitar (steel)", // = 25
		"Electric Guitar (jazz)", // = 26
		"Electric Guitar (clean)", // = 27
		"Electric Guitar (muted)", // = 28
		"Overdriven Guitar", // = 29
		"Distortion Guitar", // = 30
		"Guitar Harmonics", // = 31
		// Bass
		"Acoustic Bass", // = 32
		"Electric Bass (finger)", // = 33
		"Electric Bass (pick)", // = 34
		"Fretless Bass", // = 35
		"Slap Bass 1", // = 36
		"Slap Bass 2", // = 37
		"Synth Bass 1", // = 38
		"Synth Bass 2", // = 39
		// Strings
		"Violin", // = 40
		"Viola", // = 41
		"Cello", // = 42
		"Contrabass", // = 43
		"Tremolo Strings", // = 44
		"Pizzicato Strings", // = 45
		"Orchestral Harp", // = 46
		"Timpani", // = 47
		// Ensemble
		"String Ensemble 1", // = 48
		"String Ensemble 2", // = 49
		"Synth Strings 1", // = 50
		"Synth Strings 2", // = 51
		"Choir Aahs", // = 52
		"Voice Oohs", // = 53
		"Synth Choir", // = 54
		"Orchestra Hit", // = 55
		// Brass
		"Trumpet", // = 56
		"Trombone", // = 57
		"Tuba", // = 58
		"Muted Trumpet", // = 59
		"French Horn", // = 60
		"Brass Section", // = 61
		"Synth Brass 1", // = 62
		"Synth Brass 2", // = 63
		// Reed
		"Soprano Sax", // = 64
		"Alto Sax", // = 65
		"Tenor Sax", // = 66
		"Baritone Sax", // = 67
		"Oboe", // = 68
		"English Horn", // = 69
		"Bassoon", // = 70
		"Clarinet", // = 71
		// Pipe
		"Piccolo", // = 72
		"Flute", // = 73
		"Recorder", // = 74
		"Pan Flute", // = 75
		"Blown bottle", // = 76
		"Shakuhachi", // = 77
		"Whistle", // = 78
		"Ocarina", // = 79
		// Synth Lead
		"Lead 1 (square)", // = 80
		"Lead 2 (sawtooth)", // = 81
		"Lead 3 (calliope)", // = 82
		"Lead 4 chiff", // = 83
		"Lead 5 (charang)", // = 84
		"Lead 6 (voice)", // = 85
		"Lead 7 (fifths)", // = 86
		"Lead 8 (bass + lead)", // = 87
		// Synth Pad
		"Pad 1 (new age)", // = 88
		"Pad 2 (warm)", // = 89
		"Pad 3 (polysynth)", // = 90
		"Pad 4 (choir)", // = 91
		"Pad 5 (bowed)", // = 92
		"Pad 6 (metallic)", // = 93
		"Pad 7 (halo)", // = 94
		"Pad 8 (sweep)", // = 95
		// Synth Effects
		"FX 1 (rain)", // = 96
		"FX 2 (soundtrack)", // = 97
		"FX 3 (crystal)", // = 98
		"FX 4 (atmosphere)", // = 99
		"FX 5 (brightness)", // = 100
		"FX 6 (goblins)", // = 101
		"FX 7 (echoes)", // = 102
		"FX 8 (sci-fi)", // = 103
		// Ethnic
		"Sitar", // = 104
		"Banjo", // = 105
		"Shamisen", // = 106
		"Koto", // = 107
		"Kalimba", // = 108
		"Bagpipe", // = 109
		"Fiddle", // = 110
		"Shanai", // = 111
		// Percussive
		"Tinkle Bell", // = 112
		"Agogo", // = 113
		"Steel Drums", // = 114
		"Woodblock", // = 115
		"Taiko Drum", // = 116
		"Melodic Tom", // = 117
		"Synth Drum", // = 118
		"Reverse Cymbal", // = 119
		// Sound effects
		"Guitar Fret Noise", // = 120
		"Breath Noise", // = 121
		"Seashore", // = 122
		"Bird Tweet", // = 123
		"Telephone Ring", // = 124
		"Helicopter", // = 125
		"Applause", // = 126
		"Gunshot" // = 127
	};

	static std::string instrument_categories[16] =
	{
		"Piano", //  = 0
		"Chromatic Percussion", // = 1
		"Organ", // = 2
		"Guitar", // = 3
		"Bass", // = 4
		"Strings", // = 5
		"Ensemble", // = 6
		"Brass", // = 7
		"Reed", // = 8
		"Pipe", // = 9
		"Synth Lead", // = 10
		"Synth Pad", // = 11
		"Synth Effects", // = 12
		"Ethnic", // = 13
		"Percussive", // = 14
		"Sound effects" // = 15
	};

	// Percussion

	// GM Standard Drum Map
	// In GM Standard Midifiles, MIDI channel 10 (0x09) is reserved for percussion instruments only. Notes recorded on midi channel 10 always produce percussion sounds when transmitted to a keyboard or synth-module that is preset to the GM midi-mapping standard. Each of the 128 different possible note numbers correlate to a unique percussive instrument, but the sound's pitch is not relative to the note number.

	 // If a Midifile is programmed to the general midi protocol results are predictable, but the sound fidelity can vary depending on the quality of the GM Sound-Source:
	static const uint8_t NUM_DRUM_INSTRUMENTS = 47;
	static std::string drum_instruments[NUM_DRUM_INSTRUMENTS] = 
	{
		"Bass Drum 2, " // = 35
		"Bass Drum 1, " // = 36
		"Side Stick/Rimshot, " // = 37
		"Snare Drum 1, " // = 38
		"Hand Clap, " // = 39
		"Snare Drum 2, " // = 40
		"Low Tom 2, " // = 41
		"Closed Hi-hat, " // = 42
		"Low Tom 1, " // = 43
		"Pedal Hi-hat, " // = 44
		"Mid Tom 2, " // = 45
		"Open Hi-hat, " // = 46
		"Mid Tom 1, " // = 47
		"High Tom 2, " // = 48
		"Crash Cymbal 1, " // = 49
		"High Tom 1, " // = 50
		"Ride Cymbal 1, " // = 51
		"Chinese Cymbal, " // = 52
		"Ride Bell, " // = 53
		"Tambourine, " // = 54
		"Splash Cymbal, " // = 55
		"Cowbell, " // = 56
		"Crash Cymbal 2, " // = 57
		"Vibra Slap, " // = 58
		"Ride Cymbal 2, " // = 59
		"High Bongo, " // = 60
		"Low Bongo, " // = 61
		"Mute High Conga, " // = 62
		"Open High Conga, " // = 63
		"Low Conga, " // = 64
		"High Timbale, " // = 65
		"Low Timbale, " // = 66
		"High Agogô, " // = 67
		"Low Agogô, " // = 68
		"Cabasa, " // = 69
		"Maracas, " // = 70
		"Short Whistle, " // = 71
		"Long Whistle, " // = 72
		"Short Güiro, " // = 73
		"Long Güiro, " // = 74
		"Claves, " // = 75
		"High Wood Block, " // = 76
		"Low Wood Block, " // = 77
		"Mute Cuíca, " // = 78
		"Open Cuíca, " // = 79
		"Mute Triangle, " // = 80
		"Open Triangle" // = 81
	};

}