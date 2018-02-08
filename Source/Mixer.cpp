/*
  ==============================================================================

    Mixer.cpp
    Created: 8 Feb 2018 3:43:22pm
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mixer.h"

//==============================================================================
Mixer::Mixer(PlutoAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    osc1.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    osc1.setRange(0.0, 2.0f);
    osc1.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(osc1);
    
    osc2.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    osc2.setRange(0.0, 2.0f);
    osc2.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(osc2);
    
    osc3.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    osc3.setRange(0.0, 2.0f);
    osc3.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(osc3);
    
    osc1Para = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc1-volume", osc1);
    osc2Para = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc2-volume", osc2);
    osc3Para = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "osc3-volume", osc3);
}

Mixer::~Mixer()
{
}

void Mixer::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.setColour(Colours::white);
    g.drawText("MIXER", titleArea, Justification::centredTop);
    
    g.drawText("O1", 53, 150, 20, 20, Justification::centredTop);
    g.drawText("O2", 77, 150, 20, 20, Justification::centredTop);
    g.drawText("O3", 103, 150, 20, 20, Justification::centredTop);
}

void Mixer::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderHeight = 175;
    int sliderWidth = 25;
    
    osc1.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    osc2.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    osc3.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
