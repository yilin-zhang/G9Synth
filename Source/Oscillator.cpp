/*
  ==============================================================================

    Oscillator.cpp
    Created: 28 Mar 2021 10:30:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Oscillator.h"

WaveTableOscillator::WaveTableOscillator(): table(nullptr), freqInHz(0.f), sampleRate(0) {}

void WaveTableOscillator::initialize(const WaveTable *waveTable, float freqInHz, int sampleRate)
{
    table = waveTable;
    this->freqInHz = freqInHz;
    this->sampleRate = sampleRate;
    phase.reset();
}

void WaveTableOscillator::resetWaveform()
{
    phase.reset();
}

void WaveTableOscillator::reset()
{
    table = nullptr;
    freqInHz = 0.f;
    sampleRate = 0;
    phase.reset();
}

float WaveTableOscillator::getNextSample()
{
    if (sampleRate == 0)
        return 0.f;

    // get a sample
    auto sample = table->getSample(phase);
    // advance the phase
    phase.advance(freqInHz / static_cast<float>(sampleRate) * 2 * juce::float_Pi);

    return sample;
}

void WaveTableOscillator::getNextBlock(juce::AudioBuffer<float> &buffer)
{
    const auto numSamples = buffer.getNumSamples();
    auto writePointer = buffer.getWritePointer(0);
    for (int i=0; i<numSamples; ++i)
        writePointer[i] = getNextSample();
}

void WaveTableOscillator::getNextBlock(float *buffer, int numSamples)
{
    for (int i=0; i<numSamples; ++i)
        buffer[i] = getNextSample();
}

void WaveTableOscillator::setFrequency(float freqInHz)
{
    this->freqInHz = freqInHz;
}

float WaveTableOscillator::getFrequency() const
{
    return freqInHz;
}

void WaveTableOscillator::shiftPitch(float cents)
{
    // TODO
}