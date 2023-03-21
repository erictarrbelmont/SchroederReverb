/*
  ==============================================================================

    ReverbEffect.cpp
    Created: 16 Mar 2023 1:01:48pm
    Author:  Jacob Stallings

  ==============================================================================
*/

#include "ReverbEffect.h"

float ReverbEffect::processSample(float x, const int c) {
    // Set all parameters for all blocks
    // Pass the sample to each of the FBCF blocks (makes 4 copies of the sample)
    // Get outputs from those blocks and sum them
    // Run thru 1 APF and get the result
    // Run that through another APF and get the result
    // return that
    
    // TODO
    return 0.f;
    
    
}


void ReverbEffect::prepareToPlay(float sampleRate, int samplesPerBlock) {
    // set sample rate, delay times
 
    
//    fbcf1.prepareToPlay(<#float sampleRate#>, <#float speed#>, <#float depth#>, <#float gain#>, <#float delayInSamples#>);
    
    // speed = 0.9 to 1.2
    // depth = 5 to 15 samples
    
}
