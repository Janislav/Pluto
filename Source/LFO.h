/*
  ==============================================================================

    LFO.h
    Created: 11 Feb 2018 3:14:43pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class LFO    : public Component
{
public:
    LFO();
    ~LFO();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
