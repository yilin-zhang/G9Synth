/*
  ==============================================================================

    RingMod.h
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "Oscillator.h"
#include "RingBuffer.h"

class RingMod
{
public:
    RingMod();
    ~RingMod();

    /**
     * Initialises the processor.
     */
    bool initialize(const juce::dsp::ProcessSpec& spec);

    /**
     * Processes the audio buffer
     * @param buffer
     */
    void process(juce::AudioBuffer<float> &buffer);

    /**
     * Releases the memory and sets the object uninitialized
     */
    void reset();

    /**
     * Clears the delay line and resets the internal state variables of the processor.
     */
    void clear();

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
    bool isInitialized;
    juce::dsp::ProcessSpec processSpec;
    struct RingModSpec
    {
        std::atomic<float> freqInHz; std::atomic<float> mix;
    } ringmodSpec;

    WaveTableOscillator lfo;
    SinWaveTable sinWaveTable;
};