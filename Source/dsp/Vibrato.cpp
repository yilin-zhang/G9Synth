/*
  ==============================================================================

    Vibrato.cpp
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Vibrato.h"

Vibrato::Vibrato(): SynthModule(), maximumDepthInS(0.f), ppRingBuffer(nullptr)
{
    vibratoSpec.freqInHz = 0.f; vibratoSpec.mix = 0.f; vibratoSpec.depthInSamples = 0.f;
}

Vibrato::~Vibrato()
{
    reset();
}

bool Vibrato::initialize(const juce::dsp::ProcessSpec &spec, float maximumDepthInS)
{
    if (maximumDepthInS <= 0)
        return false;

    if (!SynthModule::initialize(spec))
        return false;

    // initialize the LFO
    sinWaveTable.initialize(4096); // the wave-table only initializes itself once
    lfo.initialize(&sinWaveTable, vibratoSpec.freqInHz, spec.sampleRate);

    auto maxDepthInSamples = static_cast<int>(round(maximumDepthInS*spec.sampleRate*2+1));

    // allocate memory for a delay line
    ppRingBuffer = new CRingBuffer<float>*[spec.numChannels];
    for (int c=0; c < spec.numChannels; c++)
    {
        ppRingBuffer[c] = new CRingBuffer<float>(maxDepthInSamples);
        ppRingBuffer[c]->setWriteIdx(static_cast<int>(round(maximumDepthInS*spec.sampleRate+1)));
    }

    // set the member variables
    this->maximumDepthInS = maximumDepthInS;
    return true;
}

void Vibrato::process(juce::AudioBuffer<float> &buffer)
{
    auto bufferSize = buffer.getNumSamples();
    // Assume the number of channels in the buffer is the same as the `numChannels`
    auto ppBuffer = buffer.getArrayOfWritePointers();

    float fOffset, freqInHz, depthInSamples;
    for (int i=0; i<bufferSize; ++i)
    {
        // get parameters
        freqInHz = vibratoSpec.freqInHz;
        depthInSamples = vibratoSpec.depthInSamples;
        // update parameters
        fOffset = lfo.getNextSample();
        lfo.setFrequency(freqInHz);
        lfo.setGain(depthInSamples);
        for (int c=0; c<processSpec.numChannels; ++c)
        {
            auto dry = ppBuffer[c][i];
            ppRingBuffer[c]->putPostInc(ppBuffer[c][i]);
            auto wet = ppRingBuffer[c]->get(fOffset);
            ppRingBuffer[c]->getPostInc(); // dummy call to keep write and read idx in sync
            ppBuffer[c][i] = wet * vibratoSpec.mix + dry * (1 - vibratoSpec.mix);
        }
    }

}

void Vibrato::reset()
{
    if (!isInitialized)
        return;

    clear();

    // release the memory
    for (int c=0; c<processSpec.numChannels; ++c)
        delete ppRingBuffer[c];
    delete ppRingBuffer;
    ppRingBuffer = nullptr;

    processSpec = {0.0, 0, 0};
    vibratoSpec.freqInHz = 0.f; vibratoSpec.mix = 0.f; vibratoSpec.depthInSamples = 0.f;
    maximumDepthInS = 0.f;

    isInitialized = false;
}

void Vibrato::clear()
{
    if (!isInitialized)
        return;

    // 1. clear the delay line
    for (int c=0; c<processSpec.numChannels; ++c)
        ppRingBuffer[c]->reset();

    // 2. reset the LFO
    lfo.reset();
}

void Vibrato::setDepth(float depthInS)
{
    if (!isInitialized)
        return;

    // 1. check if the variable is in the range (0~maxDepthInSampels)
    if (depthInS <= 0 || depthInS >= maximumDepthInS)
        return;

    // 2. set the depth
    vibratoSpec.depthInSamples = static_cast<float>(depthInS * processSpec.sampleRate);
}

void Vibrato::setFrequency(float freqInHz)
{
    if (!isInitialized)
        return;

    // 1. check the frequency is not less than 0
    if (freqInHz <= 0)
        freqInHz = 0.f;

    // 2. set the frequency
    vibratoSpec.freqInHz = freqInHz;
}

void Vibrato::setMix(float value)
{
    if (!isInitialized)
        return;

    // 1. bound the value inside 0~1
    if (value > 1.f)
        value = 1.f;
    else if (value < 0.f)
        value = 0.f;

    // 2. set the mix in vibratoSpec
    vibratoSpec.mix = value;
}

float Vibrato::getMix()
{
    return vibratoSpec.mix;
}

float Vibrato::getDepth()
{
    return vibratoSpec.depthInSamples;
}

float Vibrato::getFrequency()
{
    return vibratoSpec.freqInHz;
}