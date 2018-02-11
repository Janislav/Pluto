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
    
    double oscVal1;
    double oscVal2;
    double oscVal3;
    
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
    
    void setWaveTypes(float* osc1, float* osc2, float* osc3)
    {
        oscWave1 = *osc1;
        oscWave2 = *osc2;
        oscWave3 = *osc3;
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
    
    double generateWaveForOsc(int waveType, double wave, double volume, int transposeValue)
    {
        double transposedFrequency = transpose(transposeValue, frequency);
        
        if(waveType == SINE)
        {
            wave = wave +  env.adsr(osc1.sinewave(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SAW)
        {
            wave = wave +  env.adsr(osc1.saw(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        if(waveType == SQUARE)
        {
            wave = wave +  env.adsr(osc1.square(transposedFrequency) * 0.5, env.trigger) * volume;
        }
        
        return wave;
    }
    
    double getWave()
    {
        double w = 0.0;
        
        w = generateWaveForOsc(oscWave1, w, osc1Volume, osc1Transpose);
        w = generateWaveForOsc(oscWave2, w, osc2Volume, osc2Transpose);
        w = generateWaveForOsc(oscWave3, w, osc3Volume, osc3Transpose);
        
        return w/3;
    }
    
    void setVolume(float* osc1V, float* osc2V, float* osc3V)
    {
        osc1Volume = *osc1V;
        osc2Volume = *osc2V;
        osc3Volume = *osc3V;
    }
    
    void setTranspose(float* t1, float* t2, float* t3)
    {
        osc1Transpose = *t1;
        osc2Transpose = *t2;
        osc3Transpose = *t3;
    }
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        env.trigger = 1;
    }
    
    void setFilterParameter(float* type, float* co, float* r)
    {
        filterType = *type;
        cutOff = *co;
        res = *r;
        
        //std::cout << "Type: " << filterType << "cutOff:" << cutOff << "res: " << res << std::endl;
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
    
    void pitchWheelMoved(int newPitchWheelValue)
    {}
    
    void controllerMoved(int controllerNumber, int newControllerValue)
    {}
    
    void setSampleRate(double newSampleRate)
    {
    }
    
    double bandFilter(double wave)
    {
        
        double w = 0.0;
        
        if(filterType == 0)
        {
            w = filter.lores(wave, cutOff, res);
        }
        if(filterType == 1)
        {
            w = filter.hires(wave, cutOff, res);
        }
        if(filterType == 2)
        {
            w = filter.bandpass(wave, cutOff, res);
        }
        
        return w;
    }
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSample)
    {
        for(int sample = 0;sample < numSample;++sample)
        {
            double wave = getWave();
            //wave = filter1.lores(wave, 100, 0.1);
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
    int osc2Transpose;
    int osc3Transpose;
    
    float osc1Volume;
    float osc2Volume;
    float osc3Volume;
    
    int oscWave1;
    int oscWave2;
    int oscWave3;
    
    int filterType;
    float cutOff;
    float res;
    
    double sampleRate;
    
    maxiEnv env;
    maxiFilter filter;
};
