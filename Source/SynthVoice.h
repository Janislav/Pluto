/*
  ==============================================================================

    SynthVoice.h
    Created: 26 Jan 2018 5:28:59pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void getParam(float* attack, float* release, float* decay, float* sustain)
    {
        env1.setAttack(double(*attack));
        env1.setRelease(double(*release));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
    }
    
    void getOscType(float* selection)
    {
        theWave = *selection;
    }
    
    double setOscType()
    {
        if(theWave == 0)
        {
            return osc1.sinewave(frequency);
        }
        if(theWave == 1)
        {
            return osc1.saw(frequency);
        }
        if(theWave == 2){
            return osc1.square(frequency);
        }
        
        return osc1.sinewave(frequency);
    }
    
    void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
    {
        filterChoice = int(*filterType);
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    
    double setEnvelope()
    {
       return env1.adsr(setOscType(), env1.trigger) * level;
    }
    
    double setFilter()
    {
        if(filterChoice == 0)
        {
            return filter1.lores(setEnvelope(), cutoff, resonance);
        }
        
        if(filterChoice == 1)
        {
            //return filter1.hires(setEnvelope(), cutoff, reso);
        }
        
        if(filterChoice == 2)
        {
            return filter1.bandpass(setEnvelope(), cutoff, resonance);

        }
        
        return 0.0;
    }
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
        env1.trigger = 1;
        //std::cout << midiNoteNumber << std::endl;
    }
    
    void stopNote(float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        if(velocity == 0)
        {
            clearCurrentNote();
        }
    }
    
    void pitchWheelMoved(int newPitchWheelValue)
    {}
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {}
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        for(int sample = 0;sample < numSample;++sample)
        {
            //double theWave = osc1.sinewave(frequency);
            //double theSound = env1.adsr(setOscType(), env1.trigger) * level;
            double filterSound = filter1.lores(setEnvelope(), 200, 0.1);
            
            for(int channel = 0;channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filterSound);
            }
            ++startSample;
        }
    }
    
private:
    double level;
    double frequency;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    int theWave;
    int filterChoice;
    float cutoff;
    float resonance;
};
