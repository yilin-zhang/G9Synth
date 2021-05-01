/*
  ==============================================================================

    Bitcrusher.h
    Created: 1 May 2021 11:47:17am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Bitcrusher
{
public:
    Bitcrusher();
    ~Bitcrusher();

    /**
     * Initialises the processor.
     */
    bool initialize(const juce::dsp::ProcessSpec& spec);

    /**
     * Releases the memory and sets the object uninitialized
     */
    void reset();

    /**
     * Clears the delay line and resets the internal state variables of the processor.
     */
    void clear();

    /**
     * Processes the audio buffer
     * @param buffer
     */
    void process(juce::AudioBuffer<float> &buffer);

    void setClockFrequency(float freqInHz);
    float getClockFrequency() const;

    void setBitDepth(float depth);
    float getBitDepth() const;

    void setMix(float value);
    float getMix() const;

private:
    bool isInitialized;
    juce::dsp::ProcessSpec processSpec;
    struct BitcrusherSpec
    {
        std::atomic<float> freqInHz; std::atomic<float> bitDepth; std::atomic<float> mix;
    } bitcrusherSpec;

    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> interpBuffer;

    juce::CatmullRomInterpolator** ppDownSampleInterp;
    juce::ZeroOrderHoldInterpolator** ppHoldInterp;
};