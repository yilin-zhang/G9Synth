/*
  ==============================================================================

    Delay.h
    Created: 7 Apr 2021 4:17:37pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include "SynthModule.h"

class Delay : public SynthModule
{
public:
    Delay();
    ~Delay() override;

    /**
     * Initializes the Delay object
     * @param spec
     * @param maximumDelayInS
     * @return
     */
    bool initialize(const juce::dsp::ProcessSpec& spec, float maximumDelayInS);
    void clear() override;
    void reset() override;
    void process(juce::AudioBuffer<float> &buffer) override;

    /**
     * Sets the FX mix
     * @param value
     */
    void setMix(float value);

    /**
     * Sets the delay feedback
     * @param value
     */
    void setFeedback(float value);

    /**
     * Sets the delay time
     * @param delayInS
     */
    void setDelayTime(float delayInS);

private:
    struct DelaySpec
    {
        std::atomic<float> mix; std::atomic<float> feedback; std::atomic<float> delayInS;
    } delaySpec;

    float maximumDelayInS;

    juce::dsp::DelayLine<float>* pDelayLine;
};
