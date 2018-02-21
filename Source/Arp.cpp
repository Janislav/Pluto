/*
  ==============================================================================

    Arp.cpp
    Created: 20 Feb 2018 4:39:16pm
    Author:  Jan Börner

  ==============================================================================
*/

#include "Arp.h"

void Arp::process(MidiBuffer& midi, int numSamples)
{    
    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (speed)))));
    
    MidiMessage msg;
    int ignore;
    
    for (MidiBuffer::Iterator it (midi); it.getNextEvent (msg, ignore);)
    {
        if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
        else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
    }
    
    midi.clear();
    
    if ((time + numSamples) >= noteDuration)
    {
        auto offset = jmax (0, jmin ((int) (noteDuration - time), numSamples - 1));
        
        if (lastNoteValue > 0)
        {
            midi.addEvent (MidiMessage::noteOff (1, lastNoteValue), offset);
            lastNoteValue = -1;
        }
        
        if (notes.size() > 0)
        {
            currentNote = (currentNote + 1) % notes.size();
            lastNoteValue = notes[currentNote];
            midi.addEvent (MidiMessage::noteOn  (1, lastNoteValue, (uint8) 127), offset);
        }
        
    }
    
    time = (time + numSamples) % noteDuration;
}
