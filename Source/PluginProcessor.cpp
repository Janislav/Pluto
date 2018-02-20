/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlutoAudioProcessor::PlutoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
releaseTime(0.1f),
decayTime(0.1f),
sustainTime(0.1f),
tree (*this, nullptr)
#endif
{

    NormalisableRange<float> attackParam(0.0f, 5000.0f);
    tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 3.0f, nullptr, nullptr);
    
    NormalisableRange<float> releaseParam(0.0f, 5000.0f);
    tree.createAndAddParameter("release", "Release", "Attack", releaseParam, 2000.0f, nullptr, nullptr);
    
    NormalisableRange<float> decayParam(0.0f, 2.0f);
    tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 1.0f, nullptr, nullptr);
    
    NormalisableRange<float> sustainParam(0.0f, 2.0f);
    tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.5f, nullptr, nullptr);
    
    NormalisableRange<float> osc1Transpose(-12, 12);
    tree.createAndAddParameter("osc1-transpose", "Osc1Transpose", "Osc1Transpose", osc1Transpose, 0, nullptr, nullptr);
    
    NormalisableRange<float> osc1Volume(0, 2);
    tree.createAndAddParameter("osc1-volume", "osc1-volume", "osc1-volume", osc1Volume, 1, nullptr, nullptr);
    
    NormalisableRange<float> osc1Wave(0, 2);
    tree.createAndAddParameter("osc1-wave", "Osc1Wave", "Osc1Wave", osc1Wave, 0, nullptr, nullptr);
    
    NormalisableRange<float> osc2Transpose(-12, 12);
    tree.createAndAddParameter("osc2-transpose", "Osc2Transpose", "Osc2Transpose", osc2Transpose, 0, nullptr, nullptr);
    
    NormalisableRange<float> osc2Volume(0, 2);
    tree.createAndAddParameter("osc2-volume", "osc2-volume", "osc2-volume", osc2Volume, 1, nullptr, nullptr);
    
    NormalisableRange<float> osc2Wave(0, 2);
    tree.createAndAddParameter("osc2-wave", "Osc2Wave", "Osc2Wave", osc2Wave, 0, nullptr, nullptr);
    
    NormalisableRange<float> osc3Transpose(-12, 12);
    tree.createAndAddParameter("osc3-transpose", "Osc3Transpose", "Osc3Transpose", osc3Transpose, 0, nullptr, nullptr);
    
    NormalisableRange<float> osc3Volume(0, 2);
    tree.createAndAddParameter("osc3-volume", "osc3-volume", "osc3-volume", osc3Volume, 1, nullptr, nullptr);
    
    NormalisableRange<float> osc3Wave(0, 2);
    tree.createAndAddParameter("osc3-wave", "Osc3Wave", "Osc3Wave", osc3Wave, 0, nullptr, nullptr);
    
    NormalisableRange<float> dryLevel(0, 1);
    tree.createAndAddParameter("dryLevel", "dryLevel", "dryLevel", dryLevel, 1, nullptr, nullptr);
    
    NormalisableRange<float> wetLevel(0, 2);
    tree.createAndAddParameter("wetLevel", "wetLevel", "wetLevel", wetLevel, 0, nullptr, nullptr);
    
    NormalisableRange<float> roomSize(0, 1);
    tree.createAndAddParameter("roomSize", "roomSize", "roomSize", roomSize, 0, nullptr, nullptr);
    
    NormalisableRange<float> damping(0, 1);
    tree.createAndAddParameter("damping", "damping", "damping", damping, 0, nullptr, nullptr);
    
    NormalisableRange<float> cutOff(20.0, 10000.0);
    tree.createAndAddParameter("cutOff", "cutOff", "cutOff", cutOff, 2000, nullptr, nullptr);
    
    NormalisableRange<float> res(1, 5);
    tree.createAndAddParameter("res", "res", "res", res, 1, nullptr, nullptr);
    
    NormalisableRange<float> lfoRate(0, 2);
    tree.createAndAddParameter("lfoRate", "lfoRate", "lfoRate", lfoRate, 0, nullptr, nullptr);
    
    synth.clearVoices();
    
    for(int i = 0;i < 5;i++)
    {
        synth.addVoice(new SynthVoice());
    }
    
    synth.clearSounds();
    synth.addSound (new SynthSound());
}

PlutoAudioProcessor::~PlutoAudioProcessor()
{
}

//==============================================================================
const String PlutoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PlutoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PlutoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PlutoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PlutoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PlutoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PlutoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PlutoAudioProcessor::setCurrentProgram (int index)
{
}

const String PlutoAudioProcessor::getProgramName (int index)
{
    return {};
}

void PlutoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PlutoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    
    reverb.setParameters(reverbParameters);
    reverb.setSampleRate(sampleRate);
    
    
    arp.notes.clear();
    arp.currentNote = 0;
    arp.lastNoteValue = -1;
    arp.time = 0.0;
    arp.rate = static_cast<float> (sampleRate);
    
    reverb.reset();
    
    synth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void PlutoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PlutoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PlutoAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    reverbParameters.dryLevel = *tree.getRawParameterValue("dryLevel");
    reverbParameters.wetLevel = *tree.getRawParameterValue("wetLevel");
    reverbParameters.roomSize = *tree.getRawParameterValue("roomSize");
    reverbParameters.damping = *tree.getRawParameterValue("damping");
    
    reverb.setParameters(reverbParameters);
    
    for(int i = 0;i< synth.getNumVoices();i++)
    {
        if((voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))))
        {
            voice->getParam(tree.getRawParameterValue("attack"), tree.getRawParameterValue("release"), tree.getRawParameterValue("decay"), tree.getRawParameterValue("sustain"));
            voice->setVolume(tree.getRawParameterValue("osc1-volume"), tree.getRawParameterValue("osc2-volume"), tree.getRawParameterValue("osc3-volume"));
            voice->setWaveTypes(tree.getRawParameterValue("osc1-wave"), tree.getRawParameterValue("osc2-wave"), tree.getRawParameterValue("osc3-wave"));
            voice->setTranspose(tree.getRawParameterValue("osc1-transpose"), tree.getRawParameterValue("osc2-transpose"), tree.getRawParameterValue("osc3-transpose"));
            voice->setFilterParameter(tree.getRawParameterValue("cutOff"), tree.getRawParameterValue("res"), tree.getRawParameterValue("lfoRate"));
        }
    }
    
    arp.process(midiMessages, buffer.getNumSamples());
    
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

//==============================================================================
bool PlutoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PlutoAudioProcessor::createEditor()
{
    return new PlutoAudioProcessorEditor (*this);
}

//==============================================================================
void PlutoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PlutoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PlutoAudioProcessor();
}
