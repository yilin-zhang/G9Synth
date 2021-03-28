/*
  ==============================================================================

    Wavetable.h
    Created: 28 Mar 2021 10:30:40am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

// https://docs.juce.com/master/tutorial_wavetable_synth.html

class Wavetable
{
public:
    Wavetable();
    ~Wavetable();

    /**
     * Sets the frequency of the wavetable in Hz
     */
    void setFrequency(float freqInHz, int sampleRate);

    /**
     * Returns the frequency in Hz
     * @return
     */
    float getFrequency();

    /**
     * Resets the read pointer
     */
    void reset();

    /**
     * Returns the next sample
     * @return
     */
    virtual float getNextSample() = 0;

    /**
     * Fills the audio block
     */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);

protected:
    float freqInHz;
    int sampleRate;
};

// Implement a wavetable buffer inside those classes
class SinWavetable : Wavetable
{
};

class SqrWavetable : Wavetable
{
};

class SawWavetable : Wavetable
{
};
