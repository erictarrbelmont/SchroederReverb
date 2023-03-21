/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 16 Mar 2023 1:01:17pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#include "AllPassFilter.h"
#include "FractionalDelay.hpp"

float AllPassFilter::processSample(float x, int channel) {
    
    float delay1 = x +(-diffusion * delay2);
    delay2 = fracDelay.processSample(delay1, channel);
    
    float y = delay2 + (diffusion * delay1);
    
    return y;
    
}

float AllPassFilter::setDelaySamples(float delayMs) {
    float numSamples;
    //fracDelay.setFs(Fs);
    numSamples = Fs * delayMs;
    return numSamples;
}

float AllPassFilter::setDiffusion(float diffusion) {
    this->diffusion = diffusion;
    return diffusion;
}


