/*
  ==============================================================================

    Mixer.cpp
    Created: 8 Feb 2018 3:43:22pm
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReverbUI.h"

//==============================================================================
ReverbUI::ReverbUI(PlutoAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    dryLevel.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    dryLevel.setRange(0.0, 1.0f);
    dryLevel.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(dryLevel);
    
    wetLevel.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    wetLevel.setRange(0.0, 1.0f);
    wetLevel.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(wetLevel);
    
    roomSize.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    roomSize.setRange(0.0, 1.0f);
    roomSize.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(roomSize);
    
    damping.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    damping.setRange(0.0, 1.0f);
    damping.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(damping);
    
    dryLevelPara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dryLevel", dryLevel);
    wetLevelPara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "wetLevel", wetLevel);
    roomSizePara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "roomSize", roomSize);
    dampingPara = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "damping", damping);
}

ReverbUI::~ReverbUI()
{
}

void ReverbUI::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.setColour(Colours::white);
    g.drawText("REVERB", titleArea, Justification::centredTop);
    
    g.drawText("Dry", 53, 150, 20, 20, Justification::centredTop);
    g.drawText("Wet", 77, 150, 20, 20, Justification::centredTop);
    g.drawText("Room", 103, 150, 20, 20, Justification::centredTop);
    g.drawText("Dam", 128, 150, 20, 20, Justification::centredTop);
}

void ReverbUI::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderHeight = 175;
    int sliderWidth = 25;
    
    dryLevel.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    wetLevel.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    roomSize.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    damping.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
