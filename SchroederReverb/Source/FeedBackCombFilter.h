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

/**
 * This C++ code defines a class called "FeedBackCombFilter" that implements
 * a comb filter with feedback. The comb filter is a type of digital filter
 * that uses a delayed version of the input signal to create a periodic "comb"
 * of peaks and dips in the frequency response. The feedback parameter
 * controls how much of the output is fed back into the input, which can create
 * resonance and sustain in the filtered signal.
 */
class FeedBackCombFilter
{
public:
    /**
     * Constructor method that creates a new instance of the FeedBackCombFilter class.
     * @param delayInSamples The delay in samples (i.e. how long the delay line should be).
     * @param speed The speed parameter.
     * @param depth The depth parameter.
     */
    FeedBackCombFilter(float delayInSamples, float speed, float depth);

    /**
     * Destructor method that cleans up any resources used by the class.
     */
    ~FeedBackCombFilter();

    /**
     * Process a block of audio samples using the filter.
     * @param buffer The audio buffer containing the samples to filter.
     */
    void processBlock(juce::AudioBuffer<float> &buffer);
    
    /**
     * Prepare the filter for playback at the given sample rate.
     * @param sampleRate The sample rate to prepare for.
     */
    void prepareToPlay(float sampleRate);

    /**
     * Process a single sample using the filter.
     * @param x The input sample to filter.
     * @param c The index of the delay line to read from.
     * @return The filtered output sample.
     */
    float processSample(float x, const int c);

    /**
     * Set the feedback level of the filter.
     * @param feedbackLevel The new feedback level.
     */
    void setFeedbackFBCF(float feedbackLevel);

private:
    float feedbackLevel = 0.f; // The current feedback level.
    FractionalDelay delay; // The fractional delay line used by the filter.
    float m[2] = {0.f}; // The previous two output samples.
};

