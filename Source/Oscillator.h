/*
  ==============================================================================

    Oscillator.h
    Created: 28 Mar 2021 10:30:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "WaveTable.h"

// Functionalities
// -

class WaveTableOscillator
{
public:
    WaveTableOscillator();
    ~WaveTableOscillator() = default;

    /**
     * Initializes the oscillator. The user have to make sure the wave-table is initialized. The class
     * will not create a copy of the wave-table.
     * @param waveTable an initialized wave table.
     * @param freqInHz
     * @param sampleRate
     */
    void initialize(const WaveTable *waveTable, float freqInHz, int sampleRate);

    /**
     * Resets the phase to 0
     */
    void resetWaveform();

    /**
     * Resets the oscillator, including resetting the pointer to the wave table to nullptr
     */
    void reset();

    /**
     * Returns the next sample
     */
    float getNextSample();

    /**
     * Fills the first channel of the audio buffer
     * @param buffer a buffer that has at least one channel
     */
    void getNextBlock (juce::AudioBuffer<float>& buffer);

    /**
     * Fills the audio buffer
     * @param buffer
     * @param numSamples
     */
    void getNextBlock (float *buffer, int numSamples);

    /**
     * Sets the frequency of the oscillator
     * @param freqInHz
     */
    void setFrequency(float freqInHz);

    /**
     * Returns the frequency in Hz
     * @return
     */
    float getFrequency() const;

    /**
     * Shifts the pitch in cents
     * @param cents
     */
    void shiftPitch(float cents);

    /**
     * Returns the pitch shift in cents
     * @return
     */
    float getPitchShift() const;

private:
    const WaveTable *table;
    float freqInHz;
    float shiftInCent;
    int sampleRate;
    juce::dsp::Phase<float> phase;
};
