/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Chorus_auv3AudioProcessor::Chorus_auv3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),   parameters (*this, nullptr),
                        m_CurrentBufferSize(0)

#endif
{
    
    // use a default samplerate and vector size here, reset it later
    m_C74PluginState = (CommonState *)GenChorus::create(44100, 64);
    GenChorus::reset(m_C74PluginState);
    
    m_InputBuffers = new t_sample *[GenChorus::num_inputs()];
    m_OutputBuffers = new t_sample *[GenChorus::num_outputs()];
    
    for (int i = 0; i < GenChorus::num_inputs(); i++) {
        m_InputBuffers[i] = NULL;
    }
    for (int i = 0; i < GenChorus::num_outputs(); i++) {
        m_OutputBuffers[i] = NULL;
    }
    
    
    // --
    parameters.createAndAddParameter ("knob",       // parameterID
                                      "Knob",       // parameter name
                                      String(),     // parameter label (suffix)
                                      NormalisableRange<float> (0.0f, 1.0f),    // range
                                      0.0f,         // default value
                                      nullptr,
                                      nullptr);

    parameters.state = state1;
    parameters.state = state2;
    
    ValueTree knob1Tree = state1.getChildWithProperty ("id", "knob");
    ValueTree knob2Tree = state2.getChildWithProperty ("id", "knob");
    
    knob1Cache.referTo (knob1Tree, "value", nullptr);
    knob2Cache.referTo (knob2Tree, "value", nullptr);
}

Chorus_auv3AudioProcessor::~Chorus_auv3AudioProcessor()
{
    GenChorus::destroy(m_C74PluginState);
}

//==============================================================================
const String Chorus_auv3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Chorus_auv3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_auv3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Chorus_auv3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Chorus_auv3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Chorus_auv3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Chorus_auv3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Chorus_auv3AudioProcessor::setCurrentProgram (int index){
    
    switch(index) {
        case 1 :
            parameters.state = state1;
            break;
        
        case 2 :
            parameters.state = state2;
            break;
    }
    String s = parameters.state.toXmlString();
    
}

const String Chorus_auv3AudioProcessor::getProgramName (int index)
{
    return {};
}

void Chorus_auv3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Chorus_auv3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Chorus_auv3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Chorus_auv3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Chorus_auv3AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    // ------------------ MIDI processing
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
        {
            uint8 pitch = m.getNoteNumber();
            if (pitch % 2 == 0) {
                parameters.state = state1;
            }
            else parameters.state = state2;
        }
        else if (m.isController()){
            uint8 ccValue = m.getControllerValue();
            
            if (parameters.state == state1){
                knob1Cache = ccValue / 127.0;
//                knob1Cache.setValue(ccValue / 127.0, NULL);
            }
            
            if (parameters.state == state2){
                knob2Cache = ccValue / 127.0;
//                knob2Cache.setValue(ccValue / 127.0, NULL);
            }
        }
    }
    
    
    
    
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    // ------------------- GEN code starts here
    assureBufferSize(buffer.getNumSamples());
    
    // fill input buffers
    for (int i = 0; i < GenChorus::num_inputs(); i++) {
        if (i < totalNumInputChannels) {
            
            for (int j = 0; j < m_CurrentBufferSize; j++) {
                m_InputBuffers[i][j] = buffer.getReadPointer(i)[j];
            }
        } else {
            memset(m_InputBuffers[i], 0, m_CurrentBufferSize *  sizeof(double));
        }
    }

    const float currentKnob = *parameters.getRawParameterValue ("knob");
    GenChorus::setparameter(m_C74PluginState, 3, currentKnob, NULL);
    
    // process audio
    GenChorus::perform(m_C74PluginState,
                           m_InputBuffers,
                           GenChorus::num_inputs(),
                           m_OutputBuffers,
                           GenChorus::num_outputs(),
                           buffer.getNumSamples());
    
    // fill output buffers
    for (int i = 0; i < totalNumOutputChannels; i++) {
        if (i < GenChorus::num_outputs()) {
            for (int j = 0; j < buffer.getNumSamples(); j++) {
                buffer.getWritePointer(i)[j] = m_OutputBuffers[i][j];
            }
        } else {
            buffer.clear (i, 0, buffer.getNumSamples());
        }
    }

}

//==============================================================================
bool Chorus_auv3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Chorus_auv3AudioProcessor::createEditor()
{
    return new Chorus_auv3AudioProcessorEditor (*this, parameters);
}

//==============================================================================
void Chorus_auv3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void Chorus_auv3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Chorus_auv3AudioProcessor();
}

//==============================================================================
// C74 added methods

void Chorus_auv3AudioProcessor::assureBufferSize(long bufferSize)
{
    if (bufferSize > m_CurrentBufferSize) {
        for (int i = 0; i < GenChorus::num_inputs(); i++) {
            if (m_InputBuffers[i]) delete m_InputBuffers[i];
            m_InputBuffers[i] = new t_sample[bufferSize];
        }
        for (int i = 0; i < GenChorus::num_outputs(); i++) {
            if (m_OutputBuffers[i]) delete m_OutputBuffers[i];
            m_OutputBuffers[i] = new t_sample[bufferSize];
        }
        
        m_CurrentBufferSize = bufferSize;
    }
}
