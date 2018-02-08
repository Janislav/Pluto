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
class Osc    : public Component, private TextButton::Listener
{
public:
    Osc(PlutoAudioProcessor&, string id, string title);
    ~Osc();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;

private:
    PlutoAudioProcessor& processor;
    
    string title;
    string id;
    
    int WAVE;
    
    TextButton waveSelector;
    Slider volume;
    Slider transpose;
    Slider ghost;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> waveVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> transposeVal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc)
};
