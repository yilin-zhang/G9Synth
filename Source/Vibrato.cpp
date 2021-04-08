/*
  ==============================================================================

    Vibrato.cpp
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Vibrato.h"

Vibrato::Vibrato():isInitialized(false)
{

}

Vibrato::~Vibrato()
{
    reset();
}

bool Vibrato::initialize(const juce::dsp::ProcessSpec &spec, int maximumDepthInSamples)
{
    if (true/*check the values here*/)
        return false;

    // allocate memory for a delay line

    // set the member variables
    this->maximumDepthInSamples = maximumDepthInSamples;
    isInitialized = true;
}

void Vibrato::process(juce::AudioBuffer<float> &buffer)
{
    if (!isInitialized)
        return;

    // DSP code:
    // ...
}

void Vibrato::reset()
{
    if (!isInitialized)
        return;

    clear();

    // release the memory

    isInitialized = false;
}

void Vibrato::clear()
{
    if (!isInitialized)
        return;

    // 1. clear the delay line

    // 2. reset the LFO
}

void Vibrato::setDepth(int depthInSamples)
{
    if (!isInitialized)
        return;

    // 1. check if the variable is in the range (0~maxDepthInSampels)
    // 2. set the depth
}

void Vibrato::setFrequency(float freqInHz)
{
    // 1. check the frequency is not less than 0

    // 2. set the frequency of the LFO

}

void Vibrato::setMix(float value)
{
    // 1. bound the value inside 0~1
    // 2. set the mix in vibratoSpec
}

float Vibrato::getMix()
{
    return vibratoSpec.mix;
}

int Vibrato::getDepth()
{
    return vibratoSpec.depthInSamples;
}


float Vibrato::getFrequency()
{
    return vibratoSpec.freqInHz;
}