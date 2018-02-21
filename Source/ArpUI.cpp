/*
 ==============================================================================
 
 Mixer.cpp
 Created: 8 Feb 2018 3:43:22pm
 Author:  Jan Börner
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpUI.h"

//==============================================================================
ArpUI::ArpUI(PlutoAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    rate.setSliderStyle(Slider::SliderStyle::Rotary);
    rate.setRange(0.1, 50000);
    rate.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(rate);
    
    speed.setSliderStyle(Slider::SliderStyle::Rotary);
    speed.setRange(-2.0, 1.1f);
    speed.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(speed);
    
    ratePara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "rate", rate);
    speedPara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "speed", speed);
}

ArpUI::~ArpUI()
{
}

void ArpUI::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.setColour(Colours::white);
    g.drawText("ARP", titleArea, Justification::centredTop);
}

void ArpUI::resized()
{
    rate.setBounds(30, 100, 70, 70);
    speed.setBounds(100,100,70,70);
}
