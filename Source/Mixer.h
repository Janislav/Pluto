/*
  ==============================================================================

    Mixer.h
    Created: 8 Feb 2018 3:43:22pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Mixer    : public Component
{
public:
    Mixer(PlutoAudioProcessor&);
    ~Mixer();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    PlutoAudioProcessor& processor;
    
    Slider osc1;
    Slider osc2;
    Slider osc3;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc1Para;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc2Para;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> osc3Para;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};
