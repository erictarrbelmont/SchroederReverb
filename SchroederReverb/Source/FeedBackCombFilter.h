/*
  ==============================================================================

    FeedBackCombFilter.h
    Created: 16 Mar 2023 12:55:40pm
    Author:  Zachary Patchen & Luke Evans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FractionalDelay.hpp"

class FeedBackCombFilter
{
public:
    FeedBackCombFilter(float speed, float depth, float gain, float delayInSamples);
    ~FeedBackCombFilter();

    void processBlock(juce::AudioBuffer<float> &buffer);
    
    void prepareToPlay(float sampleRate);
    float processSample(float x, const int c);

    
private:
    juce::AudioBuffer<float> buffer;
    int bufferIndex;
    int bufferLength;
    float delayTime;
    float feedbackLevel;
    double sampleRate;
    
    FractionalDelay delay;
};


