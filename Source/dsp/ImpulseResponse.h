/*
  ==============================================================================

    ImpulseResponse.h
    Created: 29 Apr 2021 10:11:25pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ImpulseResponse
{
public:
    ImpulseResponse();
    ~ImpulseResponse();

    /**
     * Initializes the ImpulseResponse object
     * @param spec
     * @return
     */
    bool initialize(const juce::dsp::ProcessSpec &spec);

    bool getInitialized() const;

    bool loadImpulseResponse(const juce::String& pathToWav);

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

    void setBypass(bool isBypassed);

    bool getBypassed() const;

    /**
     * Sets the FX mix
     * @param value
     */
    void setMix(float value);

    float getMix() const;

private:
    bool isInitialized;
    juce::dsp::ProcessSpec processSpec;
    struct ImpulseResponseSpec
    {
        std::atomic<bool> isBypassed; std::atomic<float> mix;
    } impulseResponseSpec;

    juce::AudioBuffer<float> dryBuffer;

    juce::dsp::Convolution convolution;
};
