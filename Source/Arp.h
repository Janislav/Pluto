/*
  ==============================================================================

    Arp.h
    Created: 20 Feb 2018 4:39:16pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Arp {
public:
    SortedSet<int> notes;
    int time;
    int lastNoteValue;
    int currentNote;
    float rate;
    float speed;
    void process(MidiBuffer& midiMessages, int numSamples);
};
