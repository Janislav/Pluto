/*
  ==============================================================================

    Envelope.h
    Created: 6 Feb 2018 11:32:34am
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component, public SliderListener
{
public:
    Envelope(PlutoAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;

private:
    PlutoAudioProcessor& processor;
    
    Slider attackSlider;
    Slider releaseSlider;
    Slider decaySlider;
    Slider sustainSlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
