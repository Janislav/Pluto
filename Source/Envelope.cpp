/*
  ==============================================================================

    Envelope.cpp
    Created: 6 Feb 2018 11:32:34am
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(PlutoAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setSize(200, 200);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0, 50.0f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    attackSlider.addListener(this);
    addAndMakeVisible(attackSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0, 5000.0f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    releaseSlider.addListener(this);
    addAndMakeVisible(releaseSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0, 2000.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    decaySlider.addListener(this);
    addAndMakeVisible(decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0, 2000.0f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    sustainSlider.addListener(this);
    addAndMakeVisible(sustainSlider);
    
    
    attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
    
    decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);
    
    g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
    g.drawText("B", 77, 150, 20, 20, Justification::centredTop);
    g.drawText("C", 103, 150, 20, 20, Justification::centredTop);
    g.drawText("D", 128, 150, 20, 20, Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderHeight = 175;
    int sliderWidth = 25;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

void Envelope::sliderValueChanged(Slider* slider)
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
