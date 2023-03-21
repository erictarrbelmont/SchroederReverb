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
    
    void setDelaySamples(int delaySamples);
    
    void prepareToPlay(float Fs);
    
    void setSpeed(float speed);
    
    void setDepth(float depth);
    
    //void procesBlock(juce::AudioBuffer<float> &buffer);
    
private:
    
    FractionalDelay fracDelay;
    float Fs;
    //2float numSamples;
    int delaySamples;
    float diffusion;
    float delay1;
    float delay2;
    
    
};
