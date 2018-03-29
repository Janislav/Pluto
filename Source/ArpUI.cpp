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
    
    modi.addItem("OFF", 1);
    modi.addItem("ON", 2);
    addAndMakeVisible(modi);
    
    speed.setSliderStyle(Slider::SliderStyle::Rotary);
    speed.setRange(-2.0, 1.1f);
    speed.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(speed);
    
    speedPara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "speed", speed);
    modePara = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "mode", modi);
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
    modi.setBounds(30, 30, 150, 50);
    speed.setBounds(110,100,70,70);
}
