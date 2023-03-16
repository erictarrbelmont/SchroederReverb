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
    
    void setTime(float delayTime);
    
    void setDiffusion(float newDiffusion);
    
private:
    
    float time;
    float diffusion;
    
};
