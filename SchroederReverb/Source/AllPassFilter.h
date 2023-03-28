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
    
    AllPassFilter(float speed, float depth, int delaySamples);
    
    float processSample(float x, const int c);
    
    void setDiffusion(float diffusion);
    float getDiffusion();
    
    void setDelaySamples(int delaySamples);
    int getDelaySamples();
    
    void prepareToPlay(float Fs);
    float getFs();
    
    void setSpeed(float speed);
    float getSpeed();
    
    void setDepth(float depth);
    float getDepth();
    
    void setGain(float gain);
    float getGain();
    
    void setFeedbackAPF(float feedbackAPF);
    float getFeedbackAPF();
    
    //void procesBlock(juce::AudioBuffer<float> &buffer);
    
private:
    
    FractionalDelay fracDelay;
    float Fs;
    int delaySamples;
    float diffusion;
    float delay1;
    float delay2[2] = {0.f};
    
    float speed;
    float depth;
    float gain;
    float feedbackAPF;
    
};
