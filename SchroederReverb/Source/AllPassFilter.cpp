/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 16 Mar 2023 1:01:17pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#include "AllPassFilter.h"
#include "FractionalDelay.hpp"

//Available set/get parameters: Fs, DelaySamples, Gain, Diffusion, Speed, Depth - Floats

AllPassFilter::AllPassFilter(float speed, float depth, float delaySamples){
    
    fracDelay.setSpeed(speed);
    
    fracDelay.setDepth(depth);
    
    fracDelay.setDelaySamples(delaySamples);
    
}

float AllPassFilter::processSample(float x, int channel) {
    
    float delay1 = x + (-diffusion * delay2[channel]);
    
    delay2[channel] = fracDelay.processSample(delay1, channel);
    
    float y = delay2[channel] + (diffusion * delay1);
    
    y = y * gain;
    
    return y;
    
}

void AllPassFilter::prepareToPlay(float Fs) { //setFs
    
    this->Fs = Fs;
    fracDelay.setFs(Fs);
    
}

float AllPassFilter::getFs() {
    return Fs;
}


void AllPassFilter::setDelaySamples(float delaySamples) {
    this-> delaySamples = delaySamples;
    fracDelay.setDelaySamples(delaySamples);
}
float AllPassFilter::getDelaySamples() {
    return delaySamples;
}


void AllPassFilter::setGain(float gain) {
    this->gain = gain;
}
float AllPassFilter::getGain() {
    return gain;
}


void AllPassFilter::setDiffusion(float diffusion) {
    this->diffusion = diffusion;
}
float AllPassFilter::getDiffusion() {
    return diffusion;
}


void AllPassFilter::setSpeed(float speed) {
    fracDelay.setSpeed(speed);
}
float AllPassFilter::getSpeed() {
    return speed;
}


void AllPassFilter::setDepth(float depth) {
    fracDelay.setDepth(depth);
}
float AllPassFilter::getDepth() {
    return depth;
}



//float AllPassFilter::setDelaySamples(float delayMs) {
//    float numSamples;
//    fracDelay.setFs(Fs);
//    numSamples = Fs * delayMs;
//    return numSamples;
//}
