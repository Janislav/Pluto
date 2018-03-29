/*
  ==============================================================================

    Filter.h
    Created: 6 Feb 2018 3:39:23pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(PlutoAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    PlutoAudioProcessor& processor;
    
    Slider filterCutOff;
    Slider filterRes;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
