/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (825, 300);
    
    
    // Decay Time Knob
    timeKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    timeKnob.setBounds(25,50,175,175);
    timeKnob.setRange(0.0,1.0,0.01);
    timeKnob.setValue(0.5);
    timeKnob.setTextValueSuffix(" Seconds");
    timeKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    addAndMakeVisible(timeKnob);
    
    timeKnobLabel.setText("Decay Time", juce::dontSendNotification);
    timeKnobLabel.attachToComponent(&timeKnob, false);
    timeKnobLabel.setJustificationType(juce::Justification::centredTop);
    timeKnobLabel.setFont(juce::Font("Times New Roman", 24.0, juce::Font::bold));
    addAndMakeVisible(timeKnobLabel);
    
    
    // Diffusion Knob
    diffKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    diffKnob.setBounds(225,50,175,175);
    diffKnob.setRange(0.0,100.0,1.0);
    diffKnob.setValue(50.0);
    diffKnob.setTextValueSuffix(" %");
    diffKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    addAndMakeVisible(diffKnob);
    
    diffKnobLabel.setText("Diffusion", juce::dontSendNotification);
    diffKnobLabel.attachToComponent(&diffKnob, false);
    diffKnobLabel.setJustificationType(juce::Justification::centredTop);
    diffKnobLabel.setFont(juce::Font("Times New Roman", 24.0, juce::Font::bold));
    addAndMakeVisible(diffKnobLabel);
    
    
    // Lowpass Filter Knob
    lowpassKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowpassKnob.setBounds(425,50,175,175);
    lowpassKnob.setRange(1000.0,20000.0,1.0);
    lowpassKnob.setValue(12000);
    lowpassKnob.setTextValueSuffix(" Hz");
    lowpassKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    addAndMakeVisible(lowpassKnob);
    
    lowpassKnobLabel.setText("LPF", juce::dontSendNotification);
    lowpassKnobLabel.attachToComponent(&lowpassKnob, false);
    lowpassKnobLabel.setJustificationType(juce::Justification::centredTop);
    lowpassKnobLabel.setFont(juce::Font("Times New Roman", 24.0, juce::Font::bold));
    addAndMakeVisible(lowpassKnobLabel);
    
    
    // Mix Knob
    mixKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixKnob.setBounds(625,50,175,175);
    mixKnob.setRange(0.0,100.0,1.0);
    mixKnob.setValue(50.0);
    mixKnob.setTextValueSuffix(" %");
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    addAndMakeVisible(mixKnob);
    
    mixKnobLabel.setText("Mix", juce::dontSendNotification);
    mixKnobLabel.attachToComponent(&mixKnob, false);
    mixKnobLabel.setJustificationType(juce::Justification::centredTop);
    mixKnobLabel.setFont(juce::Font("Times New Roman", 24.0, juce::Font::bold));
    addAndMakeVisible(mixKnobLabel);
    
    
    // Plugin Title
    title.setText("Schroeder Reverb", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setBounds(288,250,250,50);
    title.setFont(juce::Font("Times New Roman", 32.0, juce::Font::bold));
    addAndMakeVisible(title);
    
}

SchroederReverbAudioProcessorEditor::~SchroederReverbAudioProcessorEditor()
{
}

//==============================================================================
void SchroederReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(juce::Colours::black.brighter(0.1));
    
}

void SchroederReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void SchroederReverbAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &timeKnob)
    {
        // auto value = slider-> getValue();
        // AudioProcessor.
        
        audioProcessor.setDecayTime(timeKnob.getValue()); // range from 0 to 1
    }
    if (slider == &diffKnob)
    {
        audioProcessor.setDiffusion(diffKnob.getValue()); // range from 0 to 100
    }
    if (slider == &mixKnob)
    {
        audioProcessor.setMix(mixKnob.getValue()); // range from 0 to 100
    }
    if (slider == &lowpassKnob)
    {
        audioProcessor.setLPF(lowpassKnob.getValue()); // range from 1000 to 20000
    }
}
