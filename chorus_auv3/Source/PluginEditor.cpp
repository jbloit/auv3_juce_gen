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
: AudioProcessorEditor (&p),
    knobSlider (Slider::LinearHorizontal, Slider::NoTextBox),
    processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    auto bounds = getBounds();
    
    knobSlider.addListener(this);
    knobSlider.setRange(0.0, 1.0);
    addAndMakeVisible (knobSlider);
    
    steppedLenLabel.setBounds(0, 0, 100, 40);
    steppedLenLabel.setText("0", NotificationType::sendNotification);
    addAndMakeVisible(steppedLenLabel);
    
    editModeButton.addListener(this);
    editModeButton.setBounds(120, 0, 40, 40);
    addAndMakeVisible(editModeButton);
    
    setSize (600, 200);
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
    g.drawFittedText ("This is an effect built with gen", getLocalBounds(), Justification::centred, 1);
}
#pragma mark -- callbacks
void Chorus_auv3AudioProcessorEditor::resized(){

    Rectangle<int> r = getLocalBounds();
    int guiElementAreaHeight = r.getHeight() / 3;
    
    int margin = guiElementAreaHeight / 4;
    r.reduce (margin, margin);
    
    int buttonHeight = guiElementAreaHeight - margin;
    
    knobSlider.setBounds (r.removeFromTop (guiElementAreaHeight).withSizeKeepingCentre (r.getWidth(), buttonHeight));
}
void Chorus_auv3AudioProcessorEditor::sliderDragStarted (Slider*){
    processor.editMode = true;
}
void Chorus_auv3AudioProcessorEditor::sliderDragEnded (Slider*){
    processor.editMode = false;
}
void Chorus_auv3AudioProcessorEditor::sliderValueChanged (Slider*){
    setParameterValue ("knobParam", knobSlider.getValue());
}

void Chorus_auv3AudioProcessorEditor::buttonClicked (Button*){
    processor.editMode = editModeButton.getToggleState();
}

//==============================================================================
void Chorus_auv3AudioProcessorEditor::timerCallback()
{
    knobSlider.setValue (getParameterValue ("knobParam"), NotificationType::dontSendNotification);
    steppedLenLabel.setText(String(processor.steppedLen), NotificationType::dontSendNotification);
    editModeButton.setToggleState(processor.editMode, NotificationType::dontSendNotification);
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
