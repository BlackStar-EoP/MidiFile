// MidiFile.cpp : Defines the entry point for the console application.
//

#include "MidiFile/MidiFile.h"

int main(int argc, char* argv[])
{
	//MidiFile m("d:/dancing queen.MID";)
	//MidiFile m("d:/n.mid");
	//MidiFile m("d:/level07.mid");
	MidiFile m("d:/black.mid");
	//MidiFile m("d:/maps.mid");
	m.dump_tracks("d:/mididumps");
}
