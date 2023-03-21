/*
  ==============================================================================

    FeedBackCombFilter.cpp
    Created: 16 Mar 2023 12:55:40pm
    Author:  Zachary Patchen & Luke Evans

  ==============================================================================
*/

#include "FeedBackCombFilter.h"

FeedBackCombFilter::FeedBackCombFilter() :
    buffer(1, 1),
    bufferIndex(0),
    bufferLength(0),
    delayTime(0.0f),
    feedbackLevel(0.0f),
    sampleRate(44100.0)
{
}

FeedBackCombFilter::~FeedBackCombFilter()
{
}

void FeedBackCombFilter::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
    bufferLength = static_cast<int>(sampleRate * delayTime);
    buffer.setSize(1, bufferLength, false, true, true);
    buffer.clear();
}


void FeedBackCombFilter::prepareToPlay(float sampleRate, float speed, float depth, float gain, float delayInSamples)
{
    delay.setFs(sampleRate);
    delay.setSpeed(speed);
    
    
}


void FeedBackCombFilter::setDelayTime(double delayTime)
{
    this->delayTime = delayTime;
    bufferLength = static_cast<int>(sampleRate * delayTime);
    buffer.setSize(1, bufferLength, false, true, true);
    buffer.clear();
    bufferIndex = 0;
}

void FeedBackCombFilter::setFeedbackLevel(float feedbackLevel)
{
    this->feedbackLevel = feedbackLevel;
}

float FeedBackCombFilter::process(float input)
{
    float output = buffer.getSample(0, bufferIndex);
    buffer.setSample(0, bufferIndex, input + feedbackLevel * output);
    bufferIndex = (bufferIndex + 1) % bufferLength;
    return output;
}

