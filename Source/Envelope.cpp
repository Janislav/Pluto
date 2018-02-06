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

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void Envelope::resized()
{

    Rectangle<int> area = getLocalBounds().reduced(40);
    
    attackSlider.setBounds(0, 10, 40, 100);
    releaseSlider.setBounds(50, 10, 40, 100);
    decaySlider.setBounds(100, 10, 40, 100);
    sustainSlider.setBounds(150, 10, 40, 100);
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
