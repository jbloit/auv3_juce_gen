/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Chorus_auv3AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, private Timer
{
public:
    Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor&);
    ~Chorus_auv3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    Slider rateSlider;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chorus_auv3AudioProcessor& processor;
    void timerCallback() override;
    void sliderValueChanged (Slider*) override;

    
    AudioProcessorParameter* getParameter (const String& paramId);
    float getParameterValue (const String& paramId);
    void setParameterValue (const String& paramId, float value);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_auv3AudioProcessorEditor)
};
