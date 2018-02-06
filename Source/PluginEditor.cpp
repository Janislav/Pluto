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
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0, 5000.0f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow,true, 40.0, 20.0);
    attackSlider.addListener(this);
    addAndMakeVisible(attackSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0, 5000.0f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow,true, 40.0, 20.0);
    releaseSlider.addListener(this);
    addAndMakeVisible(releaseSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0, 5000.0f);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow,true, 40.0, 20.0);
    decaySlider.addListener(this);
    addAndMakeVisible(decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0, 5000.0f);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow,true, 40.0, 20.0);
    sustainSlider.addListener(this);
    addAndMakeVisible(sustainSlider);
    
    attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
    
    decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    attackSlider.setBounds(10, 10, 40, 100);
    releaseSlider.setBounds(100, 10, 40, 100);
    decaySlider.setBounds(200, 10, 40, 100);
    sustainSlider.setBounds(300, 10, 40, 100);
}

void PlutoAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if(slider == &attackSlider)
    {
        processor.attackTime = attackSlider.getValue();
    }
    
    if(slider == &releaseSlider)
    {
        processor.releaseTime = releaseSlider.getValue();
    }
    
    if(slider == &decaySlider)
    {
        processor.decayTime = decaySlider.getValue();
    }
    
    if(slider == &sustainSlider)
    {
        processor.sustainTime = sustainSlider.getValue();
    }
}
