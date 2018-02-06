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
    
    NormalisableRange<float> attackParam(0.1f, 5000.0f);
    tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    tree.createAndAddParameter("release", "Release", "Attack", releaseParam, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> decayParam(0.1f, 5000.0f);
    tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> sustainParam(0.1f, 5000.0f);
    tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> wavetypeParam(0, 2);
    tree.createAndAddParameter("wavetype", "Wavetype", "Wavetype", wavetypeParam, 0, nullptr, nullptr);
    
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    /*
    wtFreq = 440;
    phase = 0;
    twSize = 1024;
    increment = wtFreq * twSize / sampleRate;
    amplitute = 0.25;
    
    for(int i=0;i<twSize;i++)
    {
        waveTable.insert(i, sin(2.0* double_Pi* i / twSize));
    }*/
    
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
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
    
    for(int i = 0;i< synth.getNumVoices();i++)
    {
        if((voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))))
        {
            voice->getParam(tree.getRawParameterValue("attack"), tree.getRawParameterValue("release"), tree.getRawParameterValue("decay"), tree.getRawParameterValue("sustain"));
            
            voice->getOscType(tree.getRawParameterValue("wavetype"));
        }
    }
    
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
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
