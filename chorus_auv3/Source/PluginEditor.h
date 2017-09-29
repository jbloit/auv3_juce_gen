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
class Chorus_auv3AudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor&);
    ~Chorus_auv3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    //==============================================================================
    AudioProcessorParameter* getParameter (const String& paramId)
    {
        if (AudioProcessor* processor = getAudioProcessor())
        {
            const OwnedArray<AudioProcessorParameter>& params = processor->getParameters();
            
            for (int i = 0; i < params.size(); ++i)
            {
                if (AudioProcessorParameterWithID* param = dynamic_cast<AudioProcessorParameterWithID*> (params[i]))
                {
                    if (param->paramID == paramId)
                        return param;
                }
            }
        }
        
        return nullptr;
    }
    
    //==============================================================================
    float getParameterValue (const String& paramId)
    {
        if (AudioProcessorParameter* param = getParameter (paramId))
            return param->getValue();
        
        return 0.0f;
    }
    
    void setParameterValue (const String& paramId, float value)
    {
        if (AudioProcessorParameter* param = getParameter (paramId))
            param->setValueNotifyingHost (value);
    }
    
    void sliderValueChanged (Slider* slider) override;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chorus_auv3AudioProcessor& processor;
    Slider midiVolume;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_auv3AudioProcessorEditor)
};
