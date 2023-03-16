/*
  ==============================================================================

    ReverbEffect.h
    Created: 16 Mar 2023 1:01:48pm
    Author:  Jacob Stallings

  ==============================================================================
*/

#pragma once

#include "AudioEffect.h"

class ReverbEffect : public AudioEffect {
public:
    
    ~ReverbEffect () override {
        AudioEffect::~AudioEffect();
    };
    
    float processSample(float x, const int c) override;
    
private:
    
//    FeedBackCombFilter fbcf1;
//    FeedBackCombFilter fbcf2;
//    FeedBackCombFilter fbcf3;
//    FeedBackCombFilter fbcf4;
//
//    AllPassFilter apf1;
//    AllPassFilter apf2;
    
    juce::String fbcf1;
    juce::String fbcf2;
    juce::String fbcf3;
    juce::String fbcf4;

    juce::String apf1;
    juce::String apf2;
    
};
