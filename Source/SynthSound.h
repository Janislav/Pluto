/*
  ==============================================================================

    SynthSound.h
    Created: 26 Jan 2018 5:28:36pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
 
public:
    bool appliesToNote(int /*midiNodeNumer*/)
    {
        return true;
    }
    
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};
