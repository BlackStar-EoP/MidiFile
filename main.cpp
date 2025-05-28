// MidiFile.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "MidiFile/MidiFile.h"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <OUTPUTDIR> <FILENAME>" << std::endl;
        std::exit(-1);
    }

    const auto outputDir = argv[1];
    const auto midiFile = argv[2];

    std::cout << "Parsing " << midiFile << std::endl;
    MidiFile m(midiFile);

    std::cout << "Dumping to: " << outputDir << std::endl;
    m.dump_tracks(outputDir);
}