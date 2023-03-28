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
    
    ReverbEffect();
    
    ~ReverbEffect () override {
        AudioEffect::~AudioEffect();
    };
    
    float processSample(float x, const int c) override;
    
    // Set diffusion => feedback level on APF
    void setDiffusion(float diffusion);
    
    // Set decay time => feedback level on FBCF
    void setTime(float gain);
    
    
private:
    
    const float DELAY_SAMPLES_FBCF1 = 1426;
    const float DELAY_SAMPLES_FBCF2 = 1781;
    const float DELAY_SAMPLES_FBCF3 = 1973;
    const float DELAY_SAMPLES_FBCF4 = 2098;
    
    const float DELAY_SAMPLES_APF1 = 240;
    const float DELAY_SAMPLES_APF2 = 82;
    
    const float MOD_DEPTH = 10;
    
    float feedbackLevel = 0.7;
    
    FeedBackCombFilter fbcf1;
    const float speedFBCF1 = 1.1492f; // frequency in Hz
//    const float depthFBCF1 = MOD_DEPTH; // percentage 0 to 1
    
    FeedBackCombFilter fbcf2;
    const float speedFBCF2 = 0.9238f;
//    const float depthFBCF2;
    
    FeedBackCombFilter fbcf3;
    const float speedFBCF3 = 1.1894f;
//    const float depthFBCF3;
    
    FeedBackCombFilter fbcf4;
    const float speedFBCF4 = 1.0929f;
//    const float depthFBCF4;
    
    AllPassFilter apf1;
    const float speedAPF1 = 0.9927f;
//    const float depthAPF1;
    
    AllPassFilter apf2;
    const float speedAPF2 = 0.9211f;
//    const float depthAPF2;
    
};
