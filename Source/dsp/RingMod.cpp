/*
  ==============================================================================

    RingMod.cpp
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "RingMod.h"

RingMod::RingMod() : SynthModule()
{
    ringmodSpec.freqInHz = 0.f;
}

RingMod::~RingMod()
{
    reset();
}

bool RingMod::initialize(const juce::dsp::ProcessSpec &spec)
{
    if (!SynthModule::initialize(spec))
        return false;

    // initialize the LFO
    sinWaveTable.initialize(4096); // the wave-table only initializes itself once
    lfo.initialize(&sinWaveTable, ringmodSpec.freqInHz, spec.sampleRate);
    lfo.setGain(1.f);

    return true;
}

void RingMod::process(juce::AudioBuffer<float> &buffer)
{
    auto ppBuffer = buffer.getArrayOfWritePointers();
    auto bufferSize = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();

    float fOffset, freqInHz, mix;
    for (int i = 0; i < bufferSize; ++i)
    {
        // get parameters
        freqInHz = ringmodSpec.freqInHz;
        mix = ringmodSpec.mix;
        // update parameters
        lfo.setFrequency(freqInHz);
        fOffset = lfo.getNextSample();
        for (int c = 0; c < numChannels; ++c)
        {
            auto dry = ppBuffer[c][i];
            auto wet = ppBuffer[c][i] * fOffset;
            ppBuffer[c][i] = wet * mix + dry * (1.f - mix);
        }
    }
}

void RingMod::reset()
{
    if (!isInitialized)
        return;

    clear();

    processSpec = {0.0, 0, 0};
    ringmodSpec.freqInHz = 0.f; ringmodSpec.mix = 0.f;

    isInitialized = false;
}

void RingMod::clear()
{
    if (!isInitialized)
        return;

    lfo.reset();
}

void RingMod::setFrequency(float freqInHz)
{
    if (!isInitialized)
        return;

    // 1. check the frequency is not less than 0
    if (freqInHz <= 0)
        freqInHz = 0.f;

    // 2. set the frequency
    ringmodSpec.freqInHz = freqInHz;
}

void RingMod::setMix(float value)
{
    if (!isInitialized)
        return;

    // 1. bound the value inside 0~1
    if (value > 1.f)
        value = 1.f;
    else if (value < 0.f)
        value = 0.f;

    // 2. set the mix in vibratoSpec
    ringmodSpec.mix = value;
}

float RingMod::getMix()
{
    return ringmodSpec.mix;
}

float RingMod::getFrequency()
{
    return ringmodSpec.freqInHz;
}