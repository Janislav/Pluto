/*
  ==============================================================================

    Osc.h
    Created: 7 Feb 2018 10:28:58am
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "waves.h"

//==============================================================================
/*
*/
class Osc    : public Component
{
public:
    Osc(PlutoAudioProcessor&);
    ~Osc();

    void paint (Graphics&) override;
    void resized() override;

private:
    PlutoAudioProcessor& processor;
    
    int WAVE;
    
    Slider volume;
    Slider transpose;
    Slider noise;
    ComboBox wave;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeNoise;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> transposeVal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc)
};
