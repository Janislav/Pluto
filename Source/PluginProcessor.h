/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Arp.h"

//==============================================================================
/**
*/
class PlutoAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PlutoAudioProcessor();
    ~PlutoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float attackTime;
    float releaseTime;
    float decayTime;
    float sustainTime;
    float sampleRate;
    bool clipped;
    
    AudioThumbnail thumbnail            { 512, formatManager, thumbnailCache };
    
    AudioProcessorValueTreeState tree;

private:
    //==============================================================================
    Synthesiser synth;
    SynthVoice* voice;
    double lastSampleRate;
    int64 nextSampleNum = 0;
    
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache  { 10 };
    
    void detectClipping(AudioSampleBuffer& buffer);
    
    Arp arp;
    
    Reverb reverb;
    Reverb::Parameters reverbParameters;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlutoAudioProcessor)
};
