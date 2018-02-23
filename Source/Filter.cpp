/*
  ==============================================================================

    Filter.cpp
    Created: 6 Feb 2018 3:39:23pm
    Author:  Jan Börner

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(PlutoAudioProcessor& p) :
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 200);
    
    filterCutOff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutOff.setRange(20.0,10000.0);
    filterCutOff.setValue(400.0);
    filterCutOff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutOff.setSkewFactorFromMidPoint(1000);
    
    filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cutOff", filterCutOff);
    
    addAndMakeVisible(filterCutOff);
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1,5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "res", filterRes);
    
    addAndMakeVisible(filterRes);
    
    lfoRate.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoRate.setRange(0,3000);
    lfoRate.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    lfoFreq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFreq.setRange(0,2000);
    lfoFreq.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    addAndMakeVisible(lfoFreq);
    
    lfoRateVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoRate", lfoRate);
    lfoFreqVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "lfoFreq", lfoFreq);
    
    addAndMakeVisible(lfoRate);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.setColour(Colours::white);
    g.drawText("LOW-PASS", titleArea, Justification::centredTop);
}

void Filter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Rectangle<int> area = getLocalBounds().reduced(40);
    filterCutOff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100,100,70,70);
    lfoRate.setBounds(60, 40, 70, 70);
    lfoFreq.setBounds(120, 40, 70, 70);
}
