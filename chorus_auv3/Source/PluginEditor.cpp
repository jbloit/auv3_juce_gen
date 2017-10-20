/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================

Chorus_auv3AudioProcessorEditor::Chorus_auv3AudioProcessorEditor (Chorus_auv3AudioProcessor& p,
                                                                  AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), valueTreeState (vts), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    knobAttachment = new SliderAttachment (valueTreeState, "knob", knobSlider);
    addAndMakeVisible (knobSlider);
    
    button1.setButtonText("1");
    addAndMakeVisible(button1);
    button1.addListener(this);
    
    button2.setButtonText("2");
    addAndMakeVisible(button2);
    button2.addListener(this);
    
    button3.setButtonText("3");
    addAndMakeVisible(button3);
    button3.addListener(this);
    
    button4.setButtonText("4");
    addAndMakeVisible(button4);
    button4.addListener(this);
    
    button5.setButtonText("5");
    addAndMakeVisible(button5);
    button5.addListener(this);
    
    button6.setButtonText("6");
    addAndMakeVisible(button6);
    button6.addListener(this);
    
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
    
    button1.setBounds (100, 40, 40, 40);
    button2.setBounds (150, 40, 40, 40);
    button3.setBounds (200, 40, 40, 40);
    button4.setBounds (250, 40, 40, 40);
    button5.setBounds (300, 40, 40, 40);
    button6.setBounds (350, 40, 40, 40);
    
    Rectangle<int> r = getLocalBounds();
    
    int guiElementAreaHeight = r.getHeight() / 3;

    
    int margin = guiElementAreaHeight / 4;
    r.reduce (margin, margin);
    
    int buttonHeight = guiElementAreaHeight - margin;
    
    knobSlider.setBounds (r.removeFromTop (guiElementAreaHeight).withSizeKeepingCentre (r.getWidth(), buttonHeight));
}

void Chorus_auv3AudioProcessorEditor::buttonClicked (Button* button){
    if (button == &button1){
        processor.setCurrentProgram(1);
        std::printf("button1\n");
    }
    if (button == &button2){
        processor.setCurrentProgram(2);
        std::printf("button2\n");
    }
    if (button == &button3){
        processor.setCurrentProgram(3);
        std::printf("button3\n");
    }
    if (button == &button4){
        processor.setCurrentProgram(4);
        std::printf("button4\n");
    }
    if (button == &button5){
        processor.setCurrentProgram(5);
        std::printf("button5\n");
    }
    if (button == &button6){
        processor.setCurrentProgram(6);
        std::printf("button6\n");
    }
}

