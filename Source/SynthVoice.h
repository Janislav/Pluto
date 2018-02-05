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
    
    void getParam(float* attack, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setRelease(double(*release));
    }
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
        env1.trigger = 1;
        std::cout << midiNoteNumber << std::endl;
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
        
        //env1.setAttack(2000);
        env1.setDecay(500);
        env1.setSustain(0.8);
        //env1.setRelease(2000);
        
        for(int sample = 0;sample < numSample;++sample)
        {
            double theWave = osc1.sinewave(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filterSound = filter1.lores(theSound, 200, 0.1);
            
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
};
