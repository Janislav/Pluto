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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    this->id = id;
    this->title = title;
    
    setSize(200, 200);
    
    WAVE = SINE;
    
    waveSelector.setName("waveSelector");
    waveSelector.setButtonText("SINE");
    waveSelector.addListener(this);
    
    transpose.setSliderStyle(Slider::SliderStyle::LinearBar);
    transpose.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    transpose.setRange(-12, 12);
    transpose.setValue(0);
    
    tune.setSliderStyle(Slider::SliderStyle::LinearBar);
    tune.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    tune.setRange(-12, 12);
    tune.setValue(0);
    
    ghost.setRange(0, 2);
    ghost.setValue(WAVE);
    
    Rectangle<int> waveSelectorForm (38,35,125,75);
    waveSelector.setBounds(waveSelectorForm);
    
    transposeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-transpose", transpose);
    tuneVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-tune", tune);
    waveVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, id+"-wave", ghost);
    
    addAndMakeVisible(waveSelector);
    addAndMakeVisible(transpose);
    addAndMakeVisible(tune);
}

Osc::~Osc()
{
}

void Osc::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    //g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText(title, titleArea, Justification::centredTop);
    
    /*Rectangle<float> area(25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);*/
}

void Osc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    transpose.setBounds(38,120,125,20);
    tune.setBounds(38,150,125,20);
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
