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
    int click = 0;
    bool sync;
    float mode;
    void process(MidiBuffer& midiMessages, int numSamples);
private:
    void modeOff(MidiBuffer& midiMessages, int numSamples);
    void modeOne(MidiBuffer& midiMessages, int numSamples);
    void modeTwo(MidiBuffer& midiMessages, int numSamples);
};
