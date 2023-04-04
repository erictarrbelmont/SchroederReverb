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
    
    // Decay Time Knob
    timeKnob.addListener(this);
    timeKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    timeKnob.setBounds(25,50,175,175);
    timeKnob.setRange(0.0,100.0,1.0);
    timeKnob.setValue(50.0);
    timeKnob.setTextValueSuffix(" %");
    timeKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    timeKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.brighter(0.1));
    timeKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::red);
    timeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    timeKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::silver.darker(0.8));
    addAndMakeVisible(timeKnob);
    
    timeKnobLabel.setText("Decay Time", juce::dontSendNotification);
    timeKnobLabel.attachToComponent(&timeKnob, false);
    timeKnobLabel.setJustificationType(juce::Justification::centredTop);
    timeKnobLabel.setFont(juce::Font("Arial Black", 22.0, juce::Font::bold));
    addAndMakeVisible(timeKnobLabel);
    
    
    // Diffusion Knob
    diffKnob.addListener(this);
    diffKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    diffKnob.setBounds(225,50,175,175);
    diffKnob.setRange(0.0,100.0,1.0);
    diffKnob.setValue(25.0);
    diffKnob.setTextValueSuffix(" %");
    diffKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    diffKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.brighter(0.1));
    diffKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    diffKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    diffKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::silver.darker(0.8));
    addAndMakeVisible(diffKnob);
    
    diffKnobLabel.setText("Diffusion", juce::dontSendNotification);
    diffKnobLabel.attachToComponent(&diffKnob, false);
    diffKnobLabel.setJustificationType(juce::Justification::centredTop);
    diffKnobLabel.setFont(juce::Font("Arial Black", 22.0, juce::Font::bold));
    addAndMakeVisible(diffKnobLabel);
    
    
    // Lowpass Filter Knob
    lowpassKnob.addListener(this);
    lowpassKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowpassKnob.setBounds(425,50,175,175);
    lowpassKnob.setRange(1000.0,20000.0,1.0);
    lowpassKnob.setValue(8000.f);
    lowpassKnob.setTextValueSuffix(" Hz");
    lowpassKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    lowpassKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.brighter(0.1));
    lowpassKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::green);
    lowpassKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    lowpassKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::silver.darker(0.8));
    addAndMakeVisible(lowpassKnob);
    
    lowpassKnobLabel.setText("LPF", juce::dontSendNotification);
    lowpassKnobLabel.attachToComponent(&lowpassKnob, false);
    lowpassKnobLabel.setJustificationType(juce::Justification::centredTop);
    lowpassKnobLabel.setFont(juce::Font("Arial Black", 22.0, juce::Font::bold));
    addAndMakeVisible(lowpassKnobLabel);
    
    
    // Mix Knob
    mixKnob.addListener(this);
    mixKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixKnob.setBounds(625,50,175,175);
    mixKnob.setRange(0.0,100.0,1.0);
    mixKnob.setValue(50.0);
    mixKnob.setTextValueSuffix(" %");
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    mixKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.brighter(0.1));
    mixKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::blueviolet);
    mixKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    mixKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::silver.darker(0.8));
    addAndMakeVisible(mixKnob);
    
    mixKnobLabel.setText("Mix", juce::dontSendNotification);
    mixKnobLabel.attachToComponent(&mixKnob, false);
    mixKnobLabel.setJustificationType(juce::Justification::centredTop);
    mixKnobLabel.setFont(juce::Font("Arial Black", 22.0, juce::Font::bold));
    addAndMakeVisible(mixKnobLabel);
    
    
    // Plugin Title
    title.setText("Schroeder Reverb", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setBounds(288,230,250,50);
    title.setFont(juce::Font("Arial Black", 32.0, juce::Font::bold));
    addAndMakeVisible(title);
    
    timeKnob.resized();
    diffKnob.resized();
    lowpassKnob.resized();
    mixKnob.resized();
    
    setResizable(true, true);
    setResizeLimits(412, 140, 1650, 560);
    setSize (825, 280);
    
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
    
    // Define plugin bounds
    auto bounds = getLocalBounds();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();
    
    // Knob bounds
    auto knobWidth = width * 175/825;
    auto knobHeight = height * 175/280;
    
    auto timeKnobX = width * 25/825;
    auto timeKnobY = height * 50/280;
    
    auto diffKnobX = width * 225/825;
    auto diffKnobY = height * 50/280;
    
    auto lowpassKnobX = width * 425/825;
    auto lowpassKnobY = height * 50/280;
    
    auto mixKnobX = width * 625/825;
    auto mixKnobY = height * 50/280;
    
    // Title bounds
    auto titleWidth = width * 250/825;
    auto titleHeight = height * 50/280;
    
    auto titleX = width * 288/825;
    auto titleY = height * 230/280;
    
    timeKnob.setBounds(timeKnobX,timeKnobY,knobWidth,knobWidth);
    diffKnob.setBounds(diffKnobX,diffKnobY,knobWidth,knobWidth);
    lowpassKnob.setBounds(lowpassKnobX,lowpassKnobY,knobWidth,knobWidth);
    mixKnob.setBounds(mixKnobX,mixKnobY,knobWidth,knobWidth);
    
    title.setBounds(titleX,titleY,titleWidth,titleHeight);
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
        audioProcessor.setDecayTime(timeKnob.getValue()); // range from 0 to 100
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
