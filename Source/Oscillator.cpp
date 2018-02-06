/*
  ==============================================================================

    Oscillator.cpp
    Created: 6 Feb 2018 9:55:14am
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(PlutoAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setSize(200, 200);
    
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype",oscMenu);
    
    addAndMakeVisible(oscMenu);
    oscMenu.addListener(this);
    oscMenu.setJustificationType(Justification::centred);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
}

void Oscillator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox* combobox)
{
    
}
