/*
  ==============================================================================

    Delay.h
    Created: 7 Apr 2021 4:17:37pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class Delay
{
public:
    Delay();
    ~Delay();

    /**
     * Initializes the Delay object
     * @param spec
     * @param maximumDelayInS
     * @return
     */
    bool initialize(const juce::dsp::ProcessSpec& spec, float maximumDelayInS);

    /**
     * Clears the samples in the delay line
     */
    void clear();

    /**
     * Releases the memory and sets the object uninitialized
     */
    void reset();

    /**
     * Processes an audio buffer
     * @param buffer
     */
    void process(juce::AudioBuffer<float> &buffer);

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
    bool isInitialized;
    juce::dsp::ProcessSpec processSpec{};
    struct DelaySpec
    {
        float mix; float feedback; float delayInS;
    } delaySpec;

    float maximumDelayInS;
    juce::dsp::DelayLine<float>** ppDelayLine{};
};
