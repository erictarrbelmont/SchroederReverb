/*
  ==============================================================================

    FeedBackCombFilter.cpp
    Created: 16 Mar 2023 12:55:40pm
    Author:  Zachary Patchen & Luke Evans

  ==============================================================================
*/

#include "FeedBackCombFilter.h"

FeedBackCombFilter::FeedBackCombFilter(float delayInSample, float feedbackLevel, float speed, float depth){
        delay.setDelaySamples(delayInSample);
        delay.setSpeed(speed);
        delay.setDepth(depth);
        this->feedbackLevel = feedbackLevel;
}

FeedBackCombFilter::~FeedBackCombFilter()
{
}

void FeedBackCombFilter::prepareToPlay(float sampleRate)
{
    delay.setFs(sampleRate);
}

float FeedBackCombFilter::processSample(float x, const int c){
    x = delay.processSample(x, c);
    x*= feedbackLevel;
    return x;
}

void FeedBackCombFilter::processBlock(juce::AudioBuffer<float> &buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    for (int c = 0; c < numChannels ; ++c){
        
        for (int n = 0; n < numSamples ; ++n){
            
            float x = buffer.getWritePointer(c) [n];
            
            x = processSample(x,c);
            buffer.getWritePointer(c) [n] = x;
        }
    }
}

