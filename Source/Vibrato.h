/*
  ==============================================================================

    Vibrato.h
    Created: 28 Mar 2021 10:14:44am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class Vibrato
{
public:
    Vibrato(int maximumDelayInSamples);
    ~Vibrato();

    /**
     * Initialises the processor.
     */
    void prepare(const juce::dsp::ProcessSpec& spec);

    /**
     * Resets the internal state variables of the processor.
     */
    void reset();

    /**
     * Sets the vibrato depth in samples
     * @param depthInSamples
     */
    void setDepth(int depthInSamples);

    /**
     * Returns the vibrato depth
     * @return
     */
    int getDepth();

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
};