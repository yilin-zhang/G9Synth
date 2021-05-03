/*
  ==============================================================================

    Bitcrusher.h
    Created: 1 May 2021 11:47:17am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include "SynthModule.h"

class Bitcrusher : public SynthModule
{
public:
    Bitcrusher();
    ~Bitcrusher() override;

    bool initialize(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;
    void clear() override;
    void process(juce::AudioBuffer<float> &buffer) override;

    void setClockFrequency(float freqInHz);
    float getClockFrequency() const;

    void setBitDepth(float depth);
    float getBitDepth() const;

    void setMix(float value);
    float getMix() const;

private:
    struct BitcrusherSpec
    {
        std::atomic<float> freqInHz; std::atomic<float> bitDepth; std::atomic<float> mix;
    } bitcrusherSpec;

    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> interpBuffer;

    juce::CatmullRomInterpolator** ppDownSampleInterp;
    juce::ZeroOrderHoldInterpolator** ppHoldInterp;
};