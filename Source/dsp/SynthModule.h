/*
  ==============================================================================

    SynthModule.h
    Created: 3 May 2021 11:37:19am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthModule
{
public:
    SynthModule() : isInitialized(false), processSpec({0, 0, 0}) {}

    virtual ~SynthModule() = default;

    /**
     * Initialises the processor.
     */

    bool getInitialized() const
    {
        return isInitialized;
    }

    /**
     * Processes the audio buffer
     * @param buffer
     */
    virtual void process(juce::AudioBuffer<float> &buffer) = 0;

    /**
     * Releases the memory and sets the object uninitialized. Only resets when the object is initialized.
     */
    virtual void reset() = 0;

    /**
     * Clears the delay line and resets the internal state variables of the processor.
     */
    virtual void clear() = 0;

protected:
    /**
     * Initializes the basic states of SynthModule. It should be called before the memory allocation
     * @param spec
     * @return
     */
    virtual bool initialize(const juce::dsp::ProcessSpec& spec)
    {
        reset();

        if (spec.numChannels < 0 || spec.maximumBlockSize < 0 || spec.sampleRate < 0)
            return false;

        isInitialized = true;
        processSpec = spec;
        return true;
    }

    bool isInitialized;
    juce::dsp::ProcessSpec processSpec;
};