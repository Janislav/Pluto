/*
  ==============================================================================

    Osc.cpp
    Created: 7 Feb 2018 10:28:58am
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Osc.h"

//==============================================================================
Osc::Osc(PlutoAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    WAVE = SINE;
    
    wave.addItem("SINE", 1);
    wave.addItem("SAW", 2);
    wave.addItem("SQUARE", 3);
    wave.addItem("COS", 4);
    wave.addItem("PHASOR", 5);
    wave.addItem("TRIANGLE", 6);
    wave.addItem("SINEBUF", 7);
    wave.addItem("SINEBUF4", 8);
    wave.addItem("SAWN", 9);
    wave.addItem("RECT", 10);
    
    volume.setSliderStyle(Slider::SliderStyle::LinearBar);
    volume.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volume.setRange(0, 2);
    
    transpose.setSliderStyle(Slider::SliderStyle::LinearBar);
    transpose.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    transpose.setRange(-12, 12, 1);

    noise.setSliderStyle(Slider::SliderStyle::LinearBar);
    noise.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    noise.setRange(0, 2);
    
    volumeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "volume", volume);
    transposeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "transpose", transpose);
    waveVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wave", wave);
    volumeNoise = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "noise", noise);
    
    addAndMakeVisible(wave);
    addAndMakeVisible(volume);
    addAndMakeVisible(transpose);
    addAndMakeVisible(noise);
}

Osc::~Osc()
{
}

void Osc::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.setColour(Colours::white);
    g.drawText("OSC", titleArea, Justification::centredTop);
}

void Osc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    wave.setBounds(38,50,125,20);
    transpose.setBounds(38,80,125,20);
    volume.setBounds(38,110,125,20);
    noise.setBounds(38,138,125,20);
}
