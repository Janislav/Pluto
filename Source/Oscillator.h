/*
  ==============================================================================

    Oscillator.h
    Created: 6 Feb 2018 9:55:14am
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component, private ComboBoxListener
{
public:
    Oscillator(PlutoAudioProcessor&);
    //Oscillator();
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox* combobox) override;

private:
    ComboBox oscMenu;
    PlutoAudioProcessor& processor;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
