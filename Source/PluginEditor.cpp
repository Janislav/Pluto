/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlutoAudioProcessorEditor::PlutoAudioProcessorEditor (PlutoAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), clippingLED("clippingLED", Colours::red, Colours::red, Colours::red), waveView(p.thumbnail)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&laf);
    setSize (466, 335);
    
    attackKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackKnob.setRange(0.0, 5000.0f);
    attackKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(attackKnob);
    
    releaseKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseKnob.setRange(0.0, 5000.0f);
    releaseKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(releaseKnob);
    
    decayKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decayKnob.setRange(0.0, 2.0f);
    decayKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(decayKnob);
    
    sustainKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainKnob.setRange(0.0, 2.0f);
    sustainKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(sustainKnob);
    
    waveSelector.addItem("SINE", 1);
    waveSelector.addItem("SAW", 2);
    waveSelector.addItem("SQUARE", 3);
    waveSelector.addItem("COS", 4);
    waveSelector.addItem("PHASOR", 5);
    waveSelector.addItem("TRIANGLE", 6);
    waveSelector.addItem("SINEBUF", 7);
    waveSelector.addItem("SINEBUF4", 8);
    waveSelector.addItem("SAWN", 9);
    waveSelector.addItem("RECT", 10);
    
    addAndMakeVisible(waveSelector);
    
    transposeSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    transposeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    transposeSlider.setRange(-12, 12, 1);
    addAndMakeVisible(transposeSlider);
    
    noiseSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    noiseSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    noiseSlider.setRange(0, 2);
    addAndMakeVisible(noiseSlider);
    
    speedKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    speedKnob.setRange(-2.0, 1.1f);
    addAndMakeVisible(speedKnob);
    
    cuttoffKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cuttoffKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    cuttoffKnob.setRange(20.0, 10000.0);
    cuttoffKnob.setSkewFactorFromMidPoint(1000);
    addAndMakeVisible(cuttoffKnob);
    
    resonanceKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceKnob.setRange(1, 5);
    resonanceKnob.setValue(1);
    resonanceKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(resonanceKnob);
    
    arp.addItem("OFF", 1);
    arp.addItem("ON", 2);
    addAndMakeVisible(arp);
    
    addAndMakeVisible(clippingLED);
    addAndMakeVisible(waveView);
    
    dryKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryKnob.setRange(0.0, 1.0f);
    dryKnob.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(dryKnob);
    
    wetKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetKnob.setRange(0.0, 1.0f);
    wetKnob.setTextBoxStyle(Slider::NoTextBox,true, 0, 0);
    addAndMakeVisible(wetKnob);
    
    roomKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomKnob.setRange(0.0, 1.0f);
    roomKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(roomKnob);
    
    dampfKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dampfKnob.setRange(0.0, 1.0f);
    dampfKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(dampfKnob);
    
    masterKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterKnob.setRange(0.0, 1.0f);
    masterKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(masterKnob);
    
    //ENVELOPE
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decayKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainKnob);
    
    //LOW-PASS
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "resonance", resonanceKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "cutoff", cuttoffKnob);
    
    //ARP
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "speed", speedKnob);
    new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "mode", arp);
    
    //OSC
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "transpose", transposeSlider);
    new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wave", waveSelector);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "noise", noiseSlider);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "volume", masterKnob);
    
    //REVERB
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dry", dryKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "wet", wetKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "room", roomKnob);
    new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dampf", dampfKnob);
}

PlutoAudioProcessorEditor::~PlutoAudioProcessorEditor()
{
}

//==============================================================================
void PlutoAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    g.setFont (Font ("Andale Mono", 14.0f, Font::plain));
    
    g.drawText("ATTACK", 71, 59, 60, 60, Justification::centredTop);
    g.drawText("RELEASE", 157, 59, 60, 60, Justification::centredTop);
    g.drawText("DECAY", 250, 59, 60, 60, Justification::centredTop);
    g.drawText("SUSTAIN", 332, 59, 60, 60, Justification::centredTop);
    
    g.drawText("TRANS:", 176, 225, 60, 60, Justification::centredTop);
    g.drawText("NO:", 289, 225, 60, 60, Justification::centredTop);
    g.drawText("SPEED", 399, 188, 60, 60, Justification::centredTop);
    
    g.drawText("LP-RES", 6, 123, 60, 60, Justification::centredTop);
    g.drawText("LP-CUT", 6, 191, 60, 60, Justification::centredTop);
    
    g.drawText("DRY", 57, 306, 60, 60, Justification::centredTop);
    g.drawText("WET", 142, 306, 60, 60, Justification::centredTop);
    g.drawText("ROOM", 244, 306, 60, 60, Justification::centredTop);
    g.drawText("DAMPF", 330, 306, 60, 60, Justification::centredTop);
    g.drawText("MASTER", 401, 291, 60, 60, Justification::centredTop);
    
    g.drawText("CLIPPING", 3, 44, 60, 60, Justification::centredTop);
    
    if(processor.clipped)
    {
        Path pp;
        pp.addEllipse(0, 0, 30, 30);
        clippingLED.setColours(Colours::red, Colours::red, Colours::red);
        clippingLED.setShape(pp, false, false, false);
    } else
    {
        Path pp;
        pp.addEllipse(0, 0, 30, 30);
        clippingLED.setColours(Colours::grey, Colours::grey, Colours::grey);
        clippingLED.setShape(pp, false, false, false);
    }
    
    /**
    const String colourString2 ("000000");
    const Colour fontColor (Colour::fromString ("FF" + colourString2));
    g.setColour (fontColor);
    g.setFont (15.0f);
     */
}

void PlutoAudioProcessorEditor::resized()
{
    attackKnob.setBounds(80, 14, 40, 40);
    releaseKnob.setBounds(163, 14, 40, 40);
    decayKnob.setBounds(259, 14, 40, 40);
    sustainKnob.setBounds(338, 14, 40, 40);
    waveSelector.setBounds(75, 217, 94, 29);
    transposeSlider.setBounds(234, 217, 57, 29);
    noiseSlider.setBounds(336, 217, 57, 29);
    speedKnob.setBounds(407, 143, 40, 40);
    cuttoffKnob.setBounds(15, 143, 40, 40);
    resonanceKnob.setBounds(15, 78, 40, 40);
    clippingLED.setBounds(14, 9, 30, 30);
    arp.setBounds(402, 78, 56, 53);
    dryKnob.setBounds(67, 261, 40, 40);
    wetKnob.setBounds(151, 261, 40, 40);
    roomKnob.setBounds(253, 261, 40, 40);
    dampfKnob.setBounds(338, 261, 40, 40);
    masterKnob.setBounds(410, 246, 40, 40);
    waveView.setBounds(75, 78, 318, 129);
}
