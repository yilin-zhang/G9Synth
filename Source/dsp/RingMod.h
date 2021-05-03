/*
  ==============================================================================

    RingMod.h
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include "SynthModule.h"
#include "Oscillator.h"
#include "RingBuffer.h"

class RingMod : public SynthModule
{
public:
    RingMod();
    ~RingMod() override;

    bool initialize(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::AudioBuffer<float> &buffer) override;
    void reset() override;
    void clear() override;

    /**
     * Sets the vibrato frequency in Hz
     * @param freqInHz
     */
    void setFrequency(float freqInHz);

    /**
     * Returns the vibrato frequncy in Hz
     * @return
     */
    float getFrequency();

    /**
     * Sets the FX mix
     * @param value
     */
    void setMix(float value);

    /**
     * Returns the FX mix
     * @param value
     */
    float getMix();

private:
    struct RingModSpec
    {
        std::atomic<float> freqInHz; std::atomic<float> mix;
    } ringmodSpec;

    WaveTableOscillator lfo;
    SinWaveTable sinWaveTable;
};