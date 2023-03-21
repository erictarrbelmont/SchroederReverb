/*
  ==============================================================================

    AllPassFilter.h
    Created: 16 Mar 2023 1:01:17pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#pragma once
#include "FractionalDelay.hpp"

class AllPassFilter{
    
public:
    AllPassFilter(){};
    
    float processSample(float x, const int c);
    
    float setDiffusion(float diffusion);
    
    float setDelaySamples(float delayMs);
    
    //void procesBlock(juce::AudioBuffer<float> &buffer);
    
private:
    
    FractionalDelay fracDelay;
    float Fs;
    float numSamples;
    float delayMs;
    float diffusion;
    float delay1;
    float delay2;
    
    
};
