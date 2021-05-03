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

    bool loadImpulseResponse(const juce::String& pathToWav);
    void setBypass(bool isBypassed);
    bool getBypassed() const;

    /**
     * Sets the FX mix
     * @param value
     */
    void setMix(float value);

    float getMix() const;

private:
    struct ImpulseResponseSpec
    {
        std::atomic<bool> isBypassed; std::atomic<float> mix;
    } impulseResponseSpec;

    juce::AudioBuffer<float> dryBuffer;

    juce::dsp::Convolution convolution;
};
