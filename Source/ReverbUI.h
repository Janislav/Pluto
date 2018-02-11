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
class ReverbUI    : public Component
{
public:
    ReverbUI(PlutoAudioProcessor&);
    ~ReverbUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    PlutoAudioProcessor& processor;
    
    Slider dryLevel;
    Slider wetLevel;
    Slider roomSize;
    Slider damping;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryLevelPara;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetLevelPara;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSizePara;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampingPara;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbUI)
};
