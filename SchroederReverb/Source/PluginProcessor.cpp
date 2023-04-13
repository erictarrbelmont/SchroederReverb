/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessor::SchroederReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "ReverbParams", createParameterLayout())
#endif
{
}

SchroederReverbAudioProcessor::~SchroederReverbAudioProcessor()
{
    
}

juce::AudioProcessorValueTreeState::ParameterLayout SchroederReverbAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back( std::make_unique<juce::AudioParameterFloat> ("mixValue", //const String& parameterID,
                                                                    "Mix" , //const String& parameterName,
                                                                   juce::NormalisableRange<float> (0.f, 1.f),
                                                                   0.f //float defaultValue
                                                                   ) );
    
    
    return {params.begin() , params.end()};
    // Smart pointers
    //std::unique_ptr<ReverbEffect> myEffect;
    
}



//==============================================================================
const juce::String SchroederReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SchroederReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SchroederReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SchroederReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SchroederReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SchroederReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SchroederReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SchroederReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SchroederReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void SchroederReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SchroederReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    reverb.prepareToPlay(sampleRate, samplesPerBlock);
    filter.setFs(sampleRate);
    
    float tr = 0.1; // 100 ms response time for smoothing
    alpha = std::exp(-log(9.f)/(sampleRate * tr));
    
    sMix.reset(sampleRate,tr);
    sFreq.reset(sampleRate,tr);
}

void SchroederReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SchroederReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SchroederReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    int numSamples = buffer.getNumSamples();

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int n = 0 ; n < numSamples ; ++n)
    {
        float val = sMix.getNextValue();
        
//        float freq = sFreq.getNextValue();
        
        if (count < 8)
            count++;
        else
        {
            count = 0;
            float freq = sFreq.skip(8);
            filter.setFreq(freq);
        }
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
        
            float x = buffer.getWritePointer(channel) [n];
            
            float w = reverb.processSample(x,channel);
            w = filter.processSample(w, channel);
            
            //smoothMix[channel] = alpha * smoothMix[channel] + (1.f - alpha) * mix;
            //float y = ((1.f-smoothMix[channel]) * x) + (smoothMix[channel] * w);
            
            float y = ((1.f - val) * x) + (val * w);
            
            buffer.getWritePointer(channel)[n] = y;
        }

        
    }
}

//==============================================================================
bool SchroederReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SchroederReverbAudioProcessor::createEditor()
{
    return new SchroederReverbAudioProcessorEditor (*this);
}

//==============================================================================
void SchroederReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SchroederReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    
}

void SchroederReverbAudioProcessor::setDecayTime(float decayValue)
{
    reverb.setTime(decayValue/100.f);
}

void SchroederReverbAudioProcessor::setDiffusion(float diffusionValue)
{
    reverb.setDiffusion(diffusionValue/100.f);
}

void SchroederReverbAudioProcessor::setMix(float mixValue)
{
    mix = mixValue/100.f;
    
    sMix.setTargetValue(mixValue/100.f);
}

void SchroederReverbAudioProcessor::setLPF(float lpfValue)
{
    lpf = lpfValue;
    //filter.setFreq(lpf);
    sFreq.setTargetValue(lpfValue);
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SchroederReverbAudioProcessor();
}
