/*
  ==============================================================================

    RecordingThumbnail.h
    Created: 4 Apr 2018 4:10:21pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class RecordingThumbnail  : public Component,
private ChangeListener
{
public:
    RecordingThumbnail(AudioThumbnail& tn) : thumbnail(tn)
    {
        thumbnail.addChangeListener (this);
    }
    
    ~RecordingThumbnail()
    {
        thumbnail.removeChangeListener (this);
    }
    
    AudioThumbnail& getAudioThumbnail()     { return thumbnail; }
    
    void setDisplayFullThumbnail (bool displayFull)
    {
        displayFullThumb = displayFull;
        repaint();
    }
    
    void paint (Graphics& g) override
    {
        
        const String colourString1 ("B8E986"); //D8D8D8
        const Colour background (Colour::fromString ("FF" + colourString1));
        
        const String colourString3 ("979797"); //B8E986
        const Colour pathcolor (Colour::fromString ("FF" + colourString3));
        
        g.fillAll (background);
        g.setColour (pathcolor);
        
        if (thumbnail.getTotalLength() > 0.0)
        {
            auto endTime = displayFullThumb ? thumbnail.getTotalLength()
            : jmax (1.0, thumbnail.getTotalLength());
            
            auto thumbArea = getLocalBounds();
            thumbnail.drawChannels (g, thumbArea.reduced (2), endTime-1, endTime, 1.0f);
        }
        else
        {
            g.setFont (14.0f);
            g.drawFittedText ("(No file recorded)", getLocalBounds(), Justification::centred, 2);
        }
    }
    
private:
    
    AudioThumbnail& thumbnail;
    
    bool displayFullThumb = false;
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &thumbnail)
            repaint();
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordingThumbnail)
};
