/*
  ==============================================================================

    Delay.cpp
    Created: 7 Apr 2021 4:17:37pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Delay.h"


Delay::Delay():
isInitialized(false), processSpec({0, 0, 0}), delaySpec({0.f, 0.f, 0.f})
{}

Delay::~Delay()
{
    clear();
}

bool Delay::initialize(const juce::dsp::ProcessSpec& spec, float maximumDelayInS)
{
    if (spec.numChannels <= 0 || maximumDelayInS <= 0.f)
        return false;

    // allocate memory
    int maximumDelayInSamples = ceil(spec.sampleRate * maximumDelayInS);
    ppDelayLine = new juce::dsp::DelayLine<float>*[spec.numChannels];
    for (int c=0; c<spec.numChannels; ++c)
    {
        ppDelayLine[c] = new juce::dsp::DelayLine<float>(maximumDelayInSamples);
        ppDelayLine[c]->prepare({spec.sampleRate, spec.maximumBlockSize, static_cast<juce::uint32>(spec.numChannels)});
    }

    processSpec = spec;
    this->maximumDelayInS = maximumDelayInS;
    isInitialized = true;

    return true;
}

void Delay::clear()
{
    // clear the delay lines
    for (int c=0; c<processSpec.numChannels; ++c)
        ppDelayLine[c]->reset();
}

void Delay::reset()
{
    if (!isInitialized)
        return;

    clear();

    // release memory
    for (int c=0; c<processSpec.numChannels; ++c)
        delete ppDelayLine[c];
    delete[] ppDelayLine;

    processSpec.numChannels = 0;
    processSpec.sampleRate = 0.0;
    maximumDelayInS = 0.f;

    delaySpec.feedback = 0.f;
    delaySpec.delayInS = 0.f;
    delaySpec.mix = 0.f;

    isInitialized = false;
}

void Delay::process(juce::AudioBuffer<float> &buffer)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    auto ppBuffer = buffer.getArrayOfWritePointers();

    for (int i=0; i<numSamples; ++i)
    {
        for (int c=0; c<numChannels; ++c)
        {
            auto sampleInLine = ppDelayLine[c]->popSample(0);
            auto dry = ppBuffer[c][i];
            auto wet = ppBuffer[c][i] + sampleInLine * delaySpec.feedback;
            ppDelayLine[c]->pushSample(0, wet);
            ppBuffer[c][i] = wet * delaySpec.mix + dry * (1 - delaySpec.mix);
        }
    }
}

void Delay::setMix(float value)
{
    if (value > 1.f)
        value = 1.f;

    if (value < 0.f)
        value = 0.f;

    delaySpec.mix = value;
}

void Delay::setFeedback(float value)
{
    if (value > 1.f)
        value = 1.f;

    if (value < 0.f)
        value = 0.f;

    delaySpec.feedback = value;
}

void Delay::setDelayTime(float value)
{
    if (value < 0.f)
        return;

    delaySpec.delayInS = value;
    for (int c=0; c<processSpec.numChannels; ++c)
        ppDelayLine[c]->setDelay(value * processSpec.sampleRate);
}

