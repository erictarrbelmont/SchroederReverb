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
    
    ~ReverbEffect () override {
        AudioEffect::~AudioEffect();
    };
    
    float processSample(float x, const int c) override;
    
    void prepareToPlay(float sampleRate, int samplesPerBlock);
    
private:
    // FBCF
    // 1426
    // 1781
    // 1973
    // 2098
    
    // APF
    // 240
    // 82
    
    FeedBackCombFilter fbcf1;
    float delaySamplesFBCF1; // constant, see Schroeder algo
    float speedFBCF1; // frequency in Hz
    float depthFBCF1; // percentage 0 to 1
    
    FeedBackCombFilter fbcf2;
    float delaySamplesFBCF2;
    float speedFBCF2;
    float depthFBCF2;
    
    FeedBackCombFilter fbcf3;
    float delaySamplesFBCF3;
    float speedFBCF3;
    float depthFBCF3;
    
    FeedBackCombFilter fbcf4;
    float delaySamplesFBCF4;
    float speedFBCF4;
    float depthFBCF4;
    
    AllPassFilter apf1;
    float delaySamplesAPF1;
    float speedAPF1;
    float depthAPF1;
    
    AllPassFilter apf2;
    float delaySamplesAPF2;
    float speedAPF2;
    float depthAPF2;
    
};
