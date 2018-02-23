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
    : AudioProcessorEditor (&p), processor (p), envGui(p), filterGui(p), o1(p), reverbUi(p), arpUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);
    addAndMakeVisible(o1);
    addAndMakeVisible(envGui);
    addAndMakeVisible(reverbUi);
    addAndMakeVisible(filterGui);
    addAndMakeVisible(arpUI);
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
}

void PlutoAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    o1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    reverbUi.setBounds(0, 200, 200, 200);
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    arpUI.setBounds(200, 200, 200, 200);
}
