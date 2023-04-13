/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ReverbEffect.h"
#include "FeedBackCombFilter.h"
#include "AllPassFilter.h"
#include "FractionalDelay.hpp"
#include "Biquad.h"

//==============================================================================
/**
*/
class SchroederReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SchroederReverbAudioProcessor();
    ~SchroederReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float decayTime;
    void setDecayTime(float decayValue);
    
    float diffusion;
    void setDiffusion(float diffusionValue);
    
    float mix;
    float smoothMix[2] = {0.f};
    float alpha = 0.999f;
    void setMix(float mixValue);
    
    float lpf;
    void setLPF(float lpfValue);

private:
    
    ReverbEffect reverb;
    Biquad filter {Biquad::FilterType::LPF, 0.7071f};
    
    juce::SmoothedValue<float,juce::ValueSmoothingTypes::Linear> sMix {0.f};
    juce::SmoothedValue<float,juce::ValueSmoothingTypes::Multiplicative> sFreq {8000.f};
    
    int count = 0;
    
    juce::AudioProcessorValueTreeState state;
    
    // Function to fill value tree
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SchroederReverbAudioProcessor)
};
