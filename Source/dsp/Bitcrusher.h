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

    /**
     * Sets the clock frequency for sampling
     * @param freqInHz
     */
    void setClockFrequency(float freqInHz);

    /**
     * Returns the clock frequency
     * @return
     */
    float getClockFrequency() const;

    /**
     * Sets the bit depth
     * It is not really a bit depth, but the number of steps on on side excluding 0
     * @param depth
     */
    void setBitDepth(float depth);

    /**
     * Returns the bit depth
     * @return
     */
    float getBitDepth() const;

    /**
     * Sets if the dithering is on
     * @param isDithering
     */
    void setDither(bool isDithering);

    /**
     * Returns true if dithering is on
     * @return
     */
    bool getDither() const;

    /**
     * Sets the FX mix
     * @param value
     */
    void setMix(float value);

    /**
     * Returns the FX mix
     * @param value
     */
    float getMix() const;

private:
    struct BitcrusherSpec
    {
        std::atomic<float> freqInHz; std::atomic<float> bitDepth; std::atomic<bool> isDithering; std::atomic<float> mix;
    } bitcrusherSpec;

    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> interpBuffer;

    juce::Random rand;

    juce::CatmullRomInterpolator** ppDownSampleInterp;
    juce::ZeroOrderHoldInterpolator** ppHoldInterp;
};