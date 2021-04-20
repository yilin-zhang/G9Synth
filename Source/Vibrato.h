/*
  ==============================================================================

    Vibrato.h
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "Oscillator.h"
#include "RingBuffer.h"

class Vibrato
{
public:
    Vibrato();
    ~Vibrato();

    /**
     * Initialises the processor.
     */
    bool initialize(const juce::dsp::ProcessSpec& spec, float maximumDepthInS);

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
     * Sets the vibrato depth in samples
     * @param depthInSamples
     */
    void setDepth(float depthInS);

    /**
     * Returns the vibrato depth in samples
     * @return
     */
    float getDepth();

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
    float maximumDepthInS;
    juce::dsp::ProcessSpec processSpec;
    WaveTableOscillator lfo;
    SinWaveTable sinWaveTable;
    CRingBuffer<float> **ppRingBuffer;
    
    struct VibratoSpec
    {
        float depthInSamples; float freqInHz; float mix;
    } vibratoSpec;
};