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
    FeedBackCombFilter(float delayInSample, float feedbackLevel, float speed, float depth);
    ~FeedBackCombFilter();

    void processBlock(juce::AudioBuffer<float> &buffer);
    
    void prepareToPlay(float sampleRate);
    float processSample(float x, const int c);

    
private:
    float feedbackLevel;
    FractionalDelay delay;
};


