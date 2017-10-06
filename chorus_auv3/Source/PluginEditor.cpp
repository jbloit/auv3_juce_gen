/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Chorus_auv3AudioProcessorEditor::Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), rateSlider (Slider::LinearHorizontal, Slider::NoTextBox)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    rateSlider.setValue (getParameterValue ("rate"), NotificationType::dontSendNotification);
    
    rateSlider.addListener (this);
    rateSlider.setRange (0.0, 1.0);
    addAndMakeVisible (rateSlider);
    
    setSize (600, 400);
    startTimer (100);
}

Chorus_auv3AudioProcessorEditor::~Chorus_auv3AudioProcessorEditor()
{
}

//==============================================================================
void Chorus_auv3AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World! this is a chorus built with gen", getLocalBounds(), Justification::centred, 1);
}

void Chorus_auv3AudioProcessorEditor::resized(){
    Rectangle<int> r = getLocalBounds();
    
    int guiElementAreaHeight = r.getHeight() / 3;

    
    int margin = guiElementAreaHeight / 4;
    r.reduce (margin, margin);
    
    int buttonHeight = guiElementAreaHeight - margin;
    
    rateSlider.setBounds (r.removeFromTop (guiElementAreaHeight).withSizeKeepingCentre (r.getWidth(), buttonHeight));
}


void Chorus_auv3AudioProcessorEditor::sliderValueChanged (Slider*){
    setParameterValue ("rate", rateSlider.getValue());
}

void Chorus_auv3AudioProcessorEditor::timerCallback()  {
    
    rateSlider.setValue (getParameterValue ("rate"), NotificationType::dontSendNotification);
}

//==============================================================================
AudioProcessorParameter* Chorus_auv3AudioProcessorEditor::getParameter (const String& paramId)
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
float Chorus_auv3AudioProcessorEditor::getParameterValue (const String& paramId)
{
    if (AudioProcessorParameter* param = getParameter (paramId))
        return param->getValue();
    
    return 0.0f;
}

void Chorus_auv3AudioProcessorEditor::setParameterValue (const String& paramId, float value)
{
    if (AudioProcessorParameter* param = getParameter (paramId))
        param->setValueNotifyingHost (value);
}
