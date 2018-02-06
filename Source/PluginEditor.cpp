/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlutoAudioProcessorEditor::PlutoAudioProcessorEditor (PlutoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGui(p), envGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);
    addAndMakeVisible(oscGui);
    addAndMakeVisible(envGui);
}

PlutoAudioProcessorEditor::~PlutoAudioProcessorEditor()
{
}

//==============================================================================
void PlutoAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PlutoAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
