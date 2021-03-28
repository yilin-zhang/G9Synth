/*
  ==============================================================================

    Wavetable.cpp
    Created: 28 Mar 2021 10:30:40am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Wavetable.h"

void Wavetable::setFrequency(float freqInHz, int sampleRate)
{
    this->freqInHz = freqInHz;
    this->sampleRate = sampleRate;
}

float Wavetable::getFrequency()
{
    return freqInHz;
}

void Wavetable::reset()
{

}

void Wavetable::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

}
