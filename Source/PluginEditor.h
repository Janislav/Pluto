/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Filter.h"
#include "Osc.h"
#include "ReverbUI.h"
#include "ArpUI.h"
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
    PlutoAudioProcessor& processor;
    
    //
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
    //
    
    Envelope envGui;
    Filter filterGui;
    ReverbUI reverbUi;
    ArpUI arpUI;
    PlutoLookAndFeel laf;
    
    
    Osc o1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlutoAudioProcessorEditor)
};
