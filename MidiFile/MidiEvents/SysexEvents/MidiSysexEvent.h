#pragma once

#include "../MidiEvent.h"

#include <sstream>

enum EMidiManufacturer : uint16_t
{
    SEQUENTIAL_CIRCUITS = 0x01u,
    BIG_BRIAR           = 0x02u,
    OCTAVE_PLATEAU      = 0x03u,
    MOOG                = 0x04u,
    PASSPORT_DESIGNS    = 0x05u,
    LEXICON             = 0x06u,
    KURZWEIL            = 0x07u,
    FENDER              = 0x08u,
    GULBRANSEN          = 0x09u,
    DELTA_LABS          = 0x0Au,
    SOUND_COMP          = 0x0Bu,
    GENERAL_ELECTRO     = 0x0Cu,
    TECHMAR             = 0x0Du,
    MATTHEWS_RESEARCH   = 0x0Eu,
    OBERHEIM            = 0x10u,
    PAIA                = 0x11u,
    SIMMONS             = 0x12u,
    DIGIDESIGN          = 0x13u,
    FAIRLIGHT           = 0x14u,
    PEAVEY              = 0x1Bu,
    JL_COOPER           = 0x15u,
    LOWERY              = 0x16u,
    LIN                 = 0x17u,
    EMU                 = 0x18u,
    BON_TEMPI           = 0x20u,
    S_I_E_L             = 0x21u,
    SYNTHEAXE           = 0x23u,
    HOHNER              = 0x24u,
    CRUMAR              = 0x25u,
    SOLTON              = 0x26u,
    JELLINGHAUS_MS      = 0x27u,
    CTS                 = 0x28u,
    PPG                 = 0x29u,
    ELKA                = 0x2Fu,
    CHEETAH             = 0x36u,
    WALDORF             = 0x3Eu,
    KAWAI               = 0x40u,
    ROLAND              = 0x41u,
    KORG                = 0x42u,
    YAMAHA              = 0x43u,
    CASIO               = 0x44u,
    AKAI                = 0x45u,
    EDUCATIONAL_USE     = 0x7Du,
    EXTENSION           = 0xFFFFu
};

std::string get_manufacturer_string(EMidiManufacturer manufacturer)
{
    std::string manufacturer_str;
    switch (manufacturer)
    {
    case SEQUENTIAL_CIRCUITS: manufacturer_str = "SEQUENTIAL_CIRCUITS"; break;
    case BIG_BRIAR: manufacturer_str = "BIG_BRIAR"; break;
    case OCTAVE_PLATEAU: manufacturer_str = "OCTAVE_PLATEAU"; break;
    case MOOG: manufacturer_str = "MOOG"; break;
    case PASSPORT_DESIGNS: manufacturer_str = "PASSPORT_DESIGNS"; break;
    case LEXICON: manufacturer_str = "LEXICON"; break;
    case KURZWEIL: manufacturer_str = "KURZWEIL"; break;
    case FENDER: manufacturer_str = "FENDER"; break;
    case GULBRANSEN: manufacturer_str = "GULBRANSEN"; break;
    case DELTA_LABS: manufacturer_str = "DELTA_LABS"; break;
    case SOUND_COMP: manufacturer_str = "SOUND_COMP"; break;
    case GENERAL_ELECTRO: manufacturer_str = "GENERAL_ELECTRO"; break;
    case TECHMAR: manufacturer_str = "TECHMAR"; break;
    case MATTHEWS_RESEARCH: manufacturer_str = "MATTHEWS_RESEARCH"; break;
    case OBERHEIM: manufacturer_str = "OBERHEIM"; break;
    case PAIA: manufacturer_str = "PAIA"; break;
    case SIMMONS: manufacturer_str = "SIMMONS"; break;
    case DIGIDESIGN: manufacturer_str = "DIGIDESIGN"; break;
    case FAIRLIGHT: manufacturer_str = "FAIRLIGHT"; break;
    case PEAVEY: manufacturer_str = "PEAVEY"; break;
    case JL_COOPER: manufacturer_str = "JL_COOPER"; break;
    case LOWERY: manufacturer_str = "LOWERY"; break;
    case LIN: manufacturer_str = "LIN"; break;
    case EMU: manufacturer_str = "EMU"; break;
    case BON_TEMPI: manufacturer_str = "BON_TEMPI"; break;
    case S_I_E_L: manufacturer_str = "S_I_E_L"; break;
    case SYNTHEAXE: manufacturer_str = "SYNTHEAXE"; break;
    case HOHNER: manufacturer_str = "HOHNER"; break;
    case CRUMAR: manufacturer_str = "CRUMAR"; break;
    case SOLTON: manufacturer_str = "SOLTON"; break;
    case JELLINGHAUS_MS: manufacturer_str = "JELLINGHAUS_MS"; break;
    case CTS: manufacturer_str = "CTS"; break;
    case PPG: manufacturer_str = "PPG"; break;
    case ELKA: manufacturer_str = "ELKA"; break;
    case CHEETAH: manufacturer_str = "CHEETAH"; break;
    case WALDORF: manufacturer_str = "WALDORF"; break;
    case KAWAI: manufacturer_str = "KAWAI"; break;
    case ROLAND: manufacturer_str = "ROLAND"; break;
    case KORG: manufacturer_str = "KORG"; break;
    case YAMAHA: manufacturer_str = "YAMAHA"; break;
    case CASIO: manufacturer_str = "CASIO"; break;
    case AKAI: manufacturer_str = "AKAI"; break;
    case EDUCATIONAL_USE: manufacturer_str = "EDUCATIONAL_USE"; break;
    case EXTENSION: manufacturer_str = "EXTENSION"; break;
    default: manufacturer_str = "UNKNOWN"; break;
    }

    return manufacturer_str;
}
class MidiSysexEvent : public MidiEvent
{
public:
	MidiSysexEvent(TICKS delta_time, uint8_t* data, uint32_t event_length, TICKS song_time)
	: MidiEvent(MidiEvent::SYSEX, delta_time, song_time)
	{
		m_message_length = event_length;
		copy_message(data, event_length);

        if (event_length > 0u)
        {
            if (data[0u] != 0u)
            {
                m_manufacturer = static_cast<EMidiManufacturer>(data[0u]);
            }
            else
            {
                if (event_length >= 3u)
                {
                    m_manufacturer = EXTENSION;
                }
            }
        }
    }

	~MidiSysexEvent()
	{
	}

	virtual std::string to_string()
	{
        std::stringstream ss;
        ss << song_time() << "(" << real_time() << ")" << "SYSEX EVENT Manufacturer = " << get_manufacturer_string(m_manufacturer);
        return ss.str();
	}

private:
    EMidiManufacturer m_manufacturer;
};
