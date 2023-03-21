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
    FeedBackCombFilter();
    ~FeedBackCombFilter();

    void setSampleRate(double sampleRate);
    void setDelayTime(double delayTime);
    void setFeedbackLevel(float feedbackLevel);
    float process(float input);
    
    void prepareToPlay(float sampleRate, float speed, float depth, float gain, float delayInSamples);
    
    
    

private:
    juce::AudioBuffer<float> buffer;
    int bufferIndex;
    int bufferLength;
    float delayTime;
    float feedbackLevel;
    double sampleRate;
    
    FractionalDelay delay;
};


