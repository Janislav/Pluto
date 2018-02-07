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
    : AudioProcessorEditor (&p), processor (p), oscGui(p), envGui(p), filterGui(p), o1(p, "osc1", "OSC1"), o2(p, "osc2", "OSC2"), o3(p, "osc3", "OSC3")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 200);
    //addAndMakeVisible(oscGui);
    //addAndMakeVisible(envGui);
    addAndMakeVisible(o1);
    addAndMakeVisible(o2);
    addAndMakeVisible(o3);
    addAndMakeVisible(envGui);
    //addAndMakeVisible(filterGui);
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
    
    //oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    o1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    o2.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    o3.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    //filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
