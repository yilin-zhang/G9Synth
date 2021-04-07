/*
  ==============================================================================

    Oscillator.cpp
    Created: 28 Mar 2021 10:30:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Oscillator.h"

WaveTableOscillator::WaveTableOscillator(): table(nullptr), freqInHz(0.f), shiftInCent(0.f), sampleRate(0) {}

void WaveTableOscillator::initialize(const WaveTable *waveTable, float freqInHz, double sampleRate)
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
    shiftInCent = 0.f;
    sampleRate = 0;
    phase.reset();
}

float WaveTableOscillator::getNextSample()
{
    if (sampleRate == 0)
        return 0.f;

    // get a sample
    auto sample = table->getSample(phase);
    float freq = 0.f;
    if (freqInHz > 8.f)
    {
        float note = log(freqInHz/440.0)/log(2) * 12 + 69 + shiftInCent/100;
        freq = 440.f * pow(2.0, (note - 69)/12);
    }
    // advance the phase
    phase.advance(freq / static_cast<float>(sampleRate) * 2 * juce::float_Pi);

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
    shiftInCent = cents;
}

float WaveTableOscillator::getPitchShift() const
{
    return shiftInCent;
}