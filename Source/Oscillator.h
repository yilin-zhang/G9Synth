/*
  ==============================================================================

    Oscillator.h
    Created: 28 Mar 2021 10:30:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "Wavetable.h"

// Functionalities
// -

class Oscillator
{
public:
    Oscillator();
    ~Oscillator();

    void processBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

private:
    Wavetable *wavetable;
};