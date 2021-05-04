/*
  ==============================================================================

    ImpulseResponse.h
    Created: 29 Apr 2021 10:11:25pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include "SynthModule.h"

class ImpulseResponse : public SynthModule
{
public:
    ImpulseResponse();
    ~ImpulseResponse() override;

    bool initialize(const juce::dsp::ProcessSpec &spec) override;
    void clear() override;
    void reset() override;
    void process(juce::AudioBuffer<float> &buffer) override;

    /**
     * Loads the impulse response
     * @param pathToWav
     * @return
     */
    bool loadImpulseResponse(const juce::String& pathToWav);

    /**
     * Sets the bypass state
     * @param isBypassed
     */
    void setBypass(bool isBypassed);

    /**
     * Returns the bypass state
     * @return
     */
    bool getBypassed() const;

    /**
     * Sets the gain
     * @param value
     */
    void setGain(float value);

    /**
     * Returns the gain
     * @param value
     */
    float getGain() const;

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
    struct ImpulseResponseSpec
    {
        std::atomic<bool> isBypassed; std::atomic<float> gain; std::atomic<float> mix;
    } impulseResponseSpec;

    juce::AudioBuffer<float> dryBuffer;

    juce::dsp::Convolution convolution;
};
