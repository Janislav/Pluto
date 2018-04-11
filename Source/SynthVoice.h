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
#include "waves.h"

#define FACT 1.059463094

class SynthVoice : public SynthesiserVoice
{
public:
    
    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void getParam(float* attack, float* release, float* decay, float* sustain)
    {
        env.setAttack(double(*attack));
        env.setRelease(double(*release));
        env.setDecay(double(*decay));
        env.setSustain(double(*sustain));
    }
    
    void setWaveTypes(float* osc1)
    {
        oscWave1 = *osc1;
    }
    
    double transpose(int v, double frequency)
    {
        if(v == 0)
        {
            return frequency;
        }
        
        unsigned int vv = abs(v);
        
        //down scale
        if(v < 0)
        {
            while(vv != 0)
            {
                frequency = frequency / FACT;
                vv--;
            }
        }else //up scale
        {
            while(vv != 0)
            {
                frequency = frequency * FACT;
                vv--;
            }
        }
        
        return frequency;
    }
    
    double generateWaveForOsc(int waveType, double wave, double volume, int transposeValue, int osc, double freq)
    {
        
        double transposedFrequency;
        

        transposedFrequency = transpose(transposeValue, freq);

        
        if(waveType == SINE)
        {
            wave = env.adsr(osc1.sinewave(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SAW)
        {
            wave = env.adsr(osc1.saw(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SQUARE)
        {
            wave = env.adsr(osc1.square(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == COS)
        {
            wave = env.adsr(osc1.coswave(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == PHASOR)
        {
            wave = env.adsr(osc1.phasor(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == TRIANGLE)
        {
            wave = env.adsr(osc1.triangle(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SINEBUF)
        {
            wave = env.adsr(osc1.sinebuf(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SINEBUF4)
        {
            wave = env.adsr(osc1.sinebuf4(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SAWN)
        {
            wave = env.adsr(osc1.sawn(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == RECT)
        {
            wave = env.adsr(osc1.rect(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        return wave;
    }
    
    double getWave()
    {
        double w = 0.0;
        
        w = generateWaveForOsc(oscWave1, w, osc1Volume, osc1Transpose, 1, frequency);
        w = w + env.adsr(osc1.noise() * 0.2, env.trigger) * noiseVolume;
        
        return w / 2;
    }
    
    void setVolume(float* osc1V, float* noiseV)
    {
        osc1Volume = *osc1V;
        noiseVolume = * noiseV;
    }
    
    void setTranspose(float* t1)
    {
        osc1Transpose = *t1;
    }
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        env.trigger = 1;
    }
    
    void setFilterParameter(float* co, float* r)
    {
        cutOff = *co;
        res = *r;
    }
    
    void pitchWheelMoved(int newPitchWheelValue)
    {}
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {}
    
    void setSampleRate(double newSampleRate)
    {
    }
    
    void stopNote(float velocity, bool allowTailOff)
    {
        env.trigger = 0;
        allowTailOff = true;
        if(velocity == 0)
        {
            clearCurrentNote();
        }
    }
    
    double bandFilter(double wave)
    {
        double w = 0.0;
        w = filter.lores(wave, cutOff, res);
        return w;
    }
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        for(int sample = 0;sample < numSample;++sample)
        {
            double wave = getWave();
            wave = bandFilter(wave);
            
            for(int channel = 0;channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, wave);
            }
            ++startSample;
        }
    }
    
private:
    double frequency;
    
    maxiOsc osc1;
    
    int osc1Transpose;
    float osc1Volume;
    int triggerCount;
    int oscWave1;
    
    float noiseVolume;
    
    float cutOff;
    float res;
    double lfoRate;
    
    int lfoWave1;
    float lfoRate1;
    int lfoWave2;
    float lfoRate2;
    int lfoWave3;
    float lfoRate3;
    
    double sampleRate;
    
    maxiEnv env;
    maxiFilter filter;
};
