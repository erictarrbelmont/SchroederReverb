/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SchroederReverbAudioProcessorEditor  : public juce::AudioProcessorEditor//,
                                             //public juce::Slider::Listener
{
public:
    SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor&);
    ~SchroederReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //virtual void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SchroederReverbAudioProcessor& audioProcessor;
    
    juce::Slider timeKnob; // fbcf g
    juce::Slider diffKnob; // apf g
    juce::Slider mixKnob;
    juce::Slider lowpassKnob;
    
    juce::Label timeKnobLabel;
    juce::Label diffKnobLabel;
    juce::Label mixKnobLabel;
    juce::Label lowpassKnobLabel;
    
    juce::Label title;
    
    juce::LookAndFeel_V4 lookAndFeelV4;
    
public:
    
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SchroederReverbAudioProcessorEditor)
};
