/*
  ==============================================================================

    FeedBackCombFilter.cpp
    Created: 16 Mar 2023 12:55:40pm
    Author:  Zachary Patchen & Luke Evans

  ==============================================================================
*/

#include "FeedBackCombFilter.h"

/**
 * Constructor method that creates a new instance of the FeedBackCombFilter class.
 * @param delayInSamples The delay in samples (i.e. how long the delay line should be).
 * @param speed The speed parameter.
 * @param depth The depth parameter.
 */
FeedBackCombFilter::FeedBackCombFilter(float delayInSamples, float speed, float depth){
    delay.setDelaySamples(delayInSamples);
    delay.setSpeed(speed);
    delay.setDepth(depth);
}

/**
 * Destructor method that cleans up any resources used by the class.
 */
FeedBackCombFilter::~FeedBackCombFilter(){
}

/**
 * Set the feedback level of the filter.
 * @param feedbackLevel The new feedback level.
 */
void FeedBackCombFilter::setFeedbackFBCF(float feedbackLevel){
    this->feedbackLevel = feedbackLevel;
}

/**
 * Prepare the filter for playback at the given sample rate.
 * @param sampleRate The sample rate to prepare for.
 */
void FeedBackCombFilter::prepareToPlay(float sampleRate){
    delay.setFs(sampleRate);
}

/**
 * Process a single sample using the filter.
 * @param x The input sample to filter.
 * @param c The index of the delay line to read from.
 * @return The filtered output sample.
 */
float FeedBackCombFilter::processSample(float x, const int c){
    float w;
    w = x + feedbackLevel * m[c];
    m[c] = delay.processSample(w, c);
    return m[c];
}

/**
 * Process a block of audio samples using the filter.
 * @param buffer The audio buffer containing the samples to filter.
 */
void FeedBackCombFilter::processBlock(juce::AudioBuffer<float> &buffer){
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


