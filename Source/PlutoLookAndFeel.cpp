/*
  ==============================================================================

    PlutoLookAndFeel.cpp
    Created: 29 Mar 2018 6:07:03pm
    Author:  Jan Börner

  ==============================================================================
*/

#include "PlutoLookAndFeel.h"


PlutoLookAndFeel::PlutoLookAndFeel()
{
    const String colourString1 ("D8D8D8");
    const Colour background (Colour::fromString ("FF" + colourString1));
    
    const String colourString2 ("000000");
    const Colour fontColor (Colour::fromString ("FF" + colourString2));
    
    const String colourString3 ("979797"); //B8E986
    const Colour pathcolor (Colour::fromString ("FF" + colourString3));
    
    setColour (ResizableWindow::backgroundColourId, background);
    setColour (ComboBox::textColourId, fontColor);
    setColour (ComboBox::arrowColourId, pathcolor);
    setColour (ComboBox::outlineColourId, pathcolor);
    setColour (ComboBox::backgroundColourId, background);
    setColour (TextButton::buttonColourId, background);
    setColour (TextButton::textColourOffId, fontColor);
}

void PlutoLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 4.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    const String colourString1 ("D8D8D8");
    const Colour background (Colour::fromString ("FF" + colourString1));
    
    const String colourString2 ("979797");
    const Colour border (Colour::fromString ("FF" + colourString2));
    
    const String colourString3 ("979797");
    const Colour pathcolor (Colour::fromString ("FF" + colourString3));
    
    // fill
    g.setColour (background);
    g.fillEllipse (rx, ry, rw, rw);
    // outline
    //g.setColour (Colour::fromFloatRGBA(166, 156, 220, 5));
    g.setColour(border);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
    
    Path p;
    const float pointerLength = radius * 0.8f;
    const float pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
    
    g.setColour (pathcolor);
    g.fillPath (p);
}

void PlutoLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int w, int h, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    const String colourString1 ("B8E986"); //D8D8D8
    const Colour fill (Colour::fromString ("FF" + colourString1));
    
    const String colourString3 ("979797"); //B8E986
    const Colour pathcolor (Colour::fromString ("FF" + colourString3));
    
    const String colourString4 ("D8D8D8"); //B8E986
    const Colour background (Colour::fromString ("FF" + colourString4));
    
    g.fillAll (slider.findColour (Slider::backgroundColourId));
    
    if (style == Slider::LinearBar)
    {
        
        g.fillAll(background);
        
        g.setColour (fill);
        g.fillRect (x, y, (int) sliderPos - x, h);
        
        g.setColour (pathcolor);
        g.drawRect (x, y, (int) sliderPos - x, h, 0);
    }
}

Font PlutoLookAndFeel::getComboBoxFont (ComboBox & box)
{
    Font font ("Andale Mono", 14.0f, Font::bold);
    return font;
}
