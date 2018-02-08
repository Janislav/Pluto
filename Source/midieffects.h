/*
  ==============================================================================

    midieffects.h
    Created: 8 Feb 2018 5:04:36pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once

#include <math.h>
#define FACT 1.059463094

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
        }
    }else //up scale
    {
        while(vv != 0)
        {
            frequency = frequency * FACT;
        }
    }
    
    return frequency;
}
