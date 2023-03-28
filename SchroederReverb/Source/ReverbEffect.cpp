/*
  ==============================================================================

    ReverbEffect.cpp
    Created: 16 Mar 2023 1:01:48pm
    Author:  Jacob Stallings

  ==============================================================================
*/

#include "ReverbEffect.h"


float ReverbEffect::processSample(float x, const int c) {
    
    float fbcfOut = fbcf1.processSample(x, c)
        + fbcf2.processSample(x, c)
        + fbcf3.processSample(x, c)
        + fbcf4.processSample(x, c);
    
    float apf1Out = apf1.processSample(fbcfOut, c);
    float y = apf2.processSample(apf1Out, c);
    
    return y;
    
}

void ReverbEffect::setDiffusion(float diffusion) {
    apf1.setDiffusion(diffusion);
    apf2.setDiffusion(diffusion);
}

void ReverbEffect::setTime(float gain) {
    fbcf1.setFeedbackFBCF(gain);
    fbcf2.setFeedbackFBCF(gain);
    fbcf3.setFeedbackFBCF(gain);
    fbcf4.setFeedbackFBCF(gain);
}

