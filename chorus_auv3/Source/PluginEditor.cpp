/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================



Chorus_auv3AudioProcessorEditor::Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), valueTreeState (vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    knobAttachment = new SliderAttachment (valueTreeState, "knob", knobSlider);
    addAndMakeVisible (knobSlider);
    
    setSize (600, 400);

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

void Chorus_auv3AudioProcessorEditor::resized(){
    Rectangle<int> r = getLocalBounds();
    
    int guiElementAreaHeight = r.getHeight() / 3;

    
    int margin = guiElementAreaHeight / 4;
    r.reduce (margin, margin);
    
    int buttonHeight = guiElementAreaHeight - margin;
    
    knobSlider.setBounds (r.removeFromTop (guiElementAreaHeight).withSizeKeepingCentre (r.getWidth(), buttonHeight));
}

