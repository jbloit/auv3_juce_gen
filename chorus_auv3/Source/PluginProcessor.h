/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GenChorus.h"

//==============================================================================
/**
*/
class Chorus_auv3AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Chorus_auv3AudioProcessor();
    ~Chorus_auv3AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    int steppedLen = 0;         // Length of recorded steps
    
protected:
    // c74: since Juce does float sample processing and Gen offers double sample
    // processing, we need to go through input and output buffers
    void assureBufferSize(long bufferSize);
    
private:
    AudioParameterFloat* knobParam;  // The one and only knob parameter
    AudioParameterBool* editParam;   // True if in edit mode
    
    Array<float> knobSteps;     // Stores knob value for each step
    const int maxNbSteps = 256;  // Maximum number of steps to store
    
    int stepIndex = 0;          // Current step index to read or write
    float currentKnobValue = 0;
    float prev_knobValue = 0;
    int knobValueChangesCount = 0;
    bool prevEditMode = false;
    float normval = 48.0;
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus_auv3AudioProcessor)
    
    CommonState				*m_C74PluginState;
    long					m_CurrentBufferSize;
    t_sample				**m_InputBuffers;
    t_sample				**m_OutputBuffers;
};
