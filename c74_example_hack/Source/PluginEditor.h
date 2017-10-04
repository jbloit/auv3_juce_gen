/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/



#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class C74_example_hackAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    C74_example_hackAudioProcessorEditor (C74GenAudioProcessor&);
    ~C74_example_hackAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    C74GenAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (C74_example_hackAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
