/*
  ==============================================================================

    ReverbEffect.cpp
    Created: 16 Mar 2023 1:01:48pm
    Author:  Jacob Stallings

  ==============================================================================
*/

#include "ReverbEffect.h"

ReverbEffect::ReverbEffect() {
    // Set all parameters for all blocks
    FeedBackCombFilter fbcf1(DELAY_SAMPLES_FBCF1, feedbackLevel, speedFBCF1, MOD_DEPTH);
    FeedBackCombFilter fbcf2(DELAY_SAMPLES_FBCF2, feedbackLevel, speedFBCF2, MOD_DEPTH);
    FeedBackCombFilter fbcf3(DELAY_SAMPLES_FBCF3, feedbackLevel, speedFBCF3, MOD_DEPTH);
    FeedBackCombFilter fbcf4(DELAY_SAMPLES_FBCF4, feedbackLevel, speedFBCF4, MOD_DEPTH);
    // APF TODO
}

float ReverbEffect::processSample(float x, const int c) {
    // Pass the sample to each of the FBCF blocks (makes 4 copies of the sample)
    // Get outputs from those blocks and sum them
    // Run thru 1 APF and get the result
    // Run that through another APF and get the result
    // return that
    
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

