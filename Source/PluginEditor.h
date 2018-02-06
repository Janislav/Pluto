/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PlutoAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener
{
public:
    PlutoAudioProcessorEditor (PlutoAudioProcessor&);
    ~PlutoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PlutoAudioProcessor& processor;
    
    Slider attackSlider;
    Slider releaseSlider;
    Slider decaySlider;
    Slider sustainSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlutoAudioProcessorEditor)
};
