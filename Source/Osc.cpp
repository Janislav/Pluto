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
Osc::Osc(PlutoAudioProcessor& p, string id, string title) :
processor(p)
{
    this->id = id;
    this->title = title;
    
    setSize(200, 200);
    
    WAVE = SINE;
    
    waveSelector.setName("waveSelector");
    waveSelector.setButtonText("SINE");
    waveSelector.addListener(this);
    
    volume.setSliderStyle(Slider::SliderStyle::LinearBar);
    volume.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volume.setRange(0, 2);
    
    transpose.setSliderStyle(Slider::SliderStyle::LinearBar);
    transpose.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    transpose.setRange(-12, 12, 1);
    
    ghost.setRange(0, 2, 1);
    ghost.setValue(WAVE);
    
    Rectangle<int> waveSelectorForm (38,35,125,75);
    waveSelector.setBounds(waveSelectorForm);
    
    volumeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-volume", volume);
    transposeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-transpose", transpose);
    waveVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-wave", ghost);
    
    addAndMakeVisible(waveSelector);
    addAndMakeVisible(volume);
    addAndMakeVisible(transpose);
}

Osc::~Osc()
{
}

void Osc::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.setColour(Colours::white);
    g.drawText(title, titleArea, Justification::centredTop);
}

void Osc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    transpose.setBounds(38,120,125,20);
    volume.setBounds(38,150,125,20);
    waveSelector.setBounds(area.removeFromTop(20));
}

void Osc::buttonClicked(Button* button)
{
    if(WAVE == SINE)
    {
        WAVE = SAW;
        waveSelector.setButtonText("SAW");
        ghost.setValue(WAVE);
        return;
    }
    if(WAVE == SAW)
    {
        WAVE = SQUARE;
        waveSelector.setButtonText("SQUARE");
        ghost.setValue(WAVE);
        return;
    }
    if(WAVE == SQUARE)
    {
        WAVE = SINE;
        waveSelector.setButtonText("SINE");
        ghost.setValue(WAVE);
        return;
    }
}
