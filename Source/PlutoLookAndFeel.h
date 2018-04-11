/*
  ==============================================================================

    PlutoLookAndFeel.h
    Created: 29 Mar 2018 6:07:03pm
    Author:  Jan Börner

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PlutoLookAndFeel : public LookAndFeel_V4
{
public:

    PlutoLookAndFeel();
    ~PlutoLookAndFeel();

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider& slider) override;
    
    
    Font getComboBoxFont (ComboBox & box) override;
};
