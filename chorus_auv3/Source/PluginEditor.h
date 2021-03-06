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



class Chorus_auv3AudioProcessorEditor  : public AudioProcessorEditor,
                                         public Button::Listener {
public:
    Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor&, AudioProcessorValueTreeState&);
    ~Chorus_auv3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
private:
    
    AudioProcessorValueTreeState& valueTreeState;
    Slider knobSlider;
    ScopedPointer<SliderAttachment> knobAttachment;
    
    TextButton button1;
    TextButton button2;
     TextButton button3;
     TextButton button4;
     TextButton button5;
     TextButton button6;
    void buttonClicked (Button* button) override;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chorus_auv3AudioProcessor& processor;


    float getParameterValue (const String& paramId);
    void setParameterValue (const String& paramId, float value);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_auv3AudioProcessorEditor)
};
