/*
  ==============================================================================

    Delay.cpp
    Created: 7 Apr 2021 4:17:37pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Delay.h"


Delay::Delay(): SynthModule(), maximumDelayInS(0.f), pDelayLine(nullptr)
{
    delaySpec.mix = 0.f; delaySpec.delayInS = 0.f; delaySpec.feedback = 0.f;
}

Delay::~Delay()
{
    reset();
}

bool Delay::initialize(const juce::dsp::ProcessSpec& spec, float maximumDelayInS)
{
    if (maximumDelayInS <= 0.f)
        return false;

    if (!SynthModule::initialize(spec))
        return false;

    int maximumDelayInSamples = ceil(spec.sampleRate * maximumDelayInS);
    pDelayLine = new juce::dsp::DelayLine<float>(maximumDelayInSamples);
    pDelayLine->prepare(spec);

    this->maximumDelayInS = maximumDelayInS;

    return true;
}

void Delay::clear()
{
    if (!isInitialized)
        return;
    // clear the delay lines
    pDelayLine->reset();
}

void Delay::reset()
{
    if (!isInitialized)
        return;

    clear();

    // release memory
    delete pDelayLine;
    pDelayLine = nullptr;

    processSpec = {0.0, 0, 0};
    delaySpec.mix = 0.f; delaySpec.delayInS = 0.f; delaySpec.feedback = 0.f;
    maximumDelayInS = 0.f;

    isInitialized = false;
}

void Delay::process(juce::AudioBuffer<float> &buffer)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    auto ppBuffer = buffer.getArrayOfWritePointers();

    float delayInS;
    for (int i=0; i<numSamples; ++i)
    {
        delayInS = delaySpec.delayInS;
        pDelayLine->setDelay(delayInS * processSpec.sampleRate);
        for (int c=0; c<numChannels; ++c)
        {
            auto sampleInLine = pDelayLine->popSample(c);
            auto dry = ppBuffer[c][i];
            auto wet = ppBuffer[c][i] + sampleInLine * delaySpec.feedback;
            pDelayLine->pushSample(c, wet);
            ppBuffer[c][i] = wet * delaySpec.mix + dry * (1 - delaySpec.mix);
        }
    }
}

void Delay::setMix(float value)
{
    if (!isInitialized)
        return;

    if (value > 1.f)
        value = 1.f;
    else if (value < 0.f)
        value = 0.f;

    delaySpec.mix = value;
}

void Delay::setFeedback(float value)
{
    if (!isInitialized)
        return;

    if (value > 1.f)
        value = 1.f;
    else if (value < 0.f)
        value = 0.f;

    delaySpec.feedback = value;
}

void Delay::setDelayTime(float value)
{
    if (!isInitialized)
        return;

    if (value < 0.f)
        value = 0.f;

    delaySpec.delayInS = value;

}

