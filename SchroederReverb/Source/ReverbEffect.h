/*
  ==============================================================================

    ReverbEffect.h
    Created: 16 Mar 2023 1:01:48pm
    Author:  Jacob Stallings

  ==============================================================================
*/

#pragma once

#include "AudioEffect.h"
#include "AllPassFilter.h"
#include "FeedBackCombFilter.h"

class ReverbEffect : public AudioEffect {
public:

    /**
     * Default constructor
     */
    //ReverbEffect() {} ;
    
    /**
     * Destructor
     */
    ~ReverbEffect () override {
        AudioEffect::~AudioEffect();
    };
    
    /**
     * Process a sample of audio using the Schroeder Reverb Algorithm
     * @param x, the sample to process
     * @param c, the channel to process
     * @return the processed sample
     */
    float processSample(float x, const int c) override;
    
    /**
     * Set the diffusion level for the reverb by setting feedback level on the AllPassFilter objects
     * @param diffusion, the new value to set
     */
    void setDiffusion(float diffusion);
    
    /**
     * Set the decay time for the reverb by setting feedback level on the FeedbackCombFilter objects
     * @param gain, the new value to set
     */
    void setTime(float gain);
    
    
private:
    
    const float DELAY_SAMPLES_FBCF1 = 1426;
    const float DELAY_SAMPLES_FBCF2 = 1781;
    const float DELAY_SAMPLES_FBCF3 = 1973;
    const float DELAY_SAMPLES_FBCF4 = 2098;
    
    const float DELAY_SAMPLES_APF1 = 240;
    const float DELAY_SAMPLES_APF2 = 82;
    
    const float MOD_DEPTH = 3; // from 1 to 10
    
    float feedbackLevel = 0.7; // 0 to 1
    
    const float speedFBCF1 = 1.1492f; // frequency in Hz, 0.9 to 1.2
    
    const float speedFBCF2 = 0.9238f;
    
    const float speedFBCF3 = 1.1894f;
    
    const float speedFBCF4 = 1.0929f;
    
    const float speedAPF1 = 0.9927f;
    
    const float speedAPF2 = 0.9211f;
    
    FeedBackCombFilter fbcf1 {DELAY_SAMPLES_FBCF1, speedFBCF1, MOD_DEPTH};
    FeedBackCombFilter fbcf2 {DELAY_SAMPLES_FBCF2, speedFBCF2, MOD_DEPTH};
    FeedBackCombFilter fbcf3 {DELAY_SAMPLES_FBCF3, speedFBCF3, MOD_DEPTH};
    FeedBackCombFilter fbcf4 {DELAY_SAMPLES_FBCF4, speedFBCF4, MOD_DEPTH};
    
    AllPassFilter apf1 {speedAPF1, MOD_DEPTH, DELAY_SAMPLES_APF1};
    AllPassFilter apf2 {speedAPF2, MOD_DEPTH, DELAY_SAMPLES_APF2};
    
};
