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
class ArpUI    : public Component
{
public:
    ArpUI(PlutoAudioProcessor&);
    ~ArpUI();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    PlutoAudioProcessor& processor;
    
    Slider rate;
    Slider speed;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> ratePara;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> speedPara;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpUI)
};
