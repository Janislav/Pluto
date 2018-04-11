/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PlutoLookAndFeel.h"
#include "RecordingThumbnail.h"

//==============================================================================
/**
*/
class PlutoAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PlutoAudioProcessorEditor (PlutoAudioProcessor&);
    ~PlutoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PlutoLookAndFeel laf;
    PlutoAudioProcessor& processor;
    
    Slider attackKnob;
    Slider releaseKnob;
    Slider decayKnob;
    Slider sustainKnob;
    ComboBox waveSelector;
    Slider transposeSlider;
    Slider noiseSlider;
    Slider speedKnob;
    ComboBox arp;
    Slider cuttoffKnob;
    Slider resonanceKnob;
    ShapeButton clippingLED;
    Label clipping;
    RecordingThumbnail waveView;
    Slider dryKnob;
    Slider wetKnob;
    Slider roomKnob;
    Slider dampfKnob;
    Slider masterKnob;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> speedAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> arpAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> transposeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> noiseAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> masterAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampfAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlutoAudioProcessorEditor)
};
