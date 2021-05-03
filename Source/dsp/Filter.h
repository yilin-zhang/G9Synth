/*
  ==============================================================================

    Filter.h
    Created: 19 Apr 2021 7:34:45pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class StateVariableFilter
{
public:
    enum class Type
    {
        lowPass,
        bandPass,
        highPass,
    };

    StateVariableFilter();
    ~StateVariableFilter();

    bool initialize(const juce::dsp::ProcessSpec& spec);
    void reset();
    void clear();

    void setType(Type);
    Type getType() const;

    void setCutoffFrequency(float freqInHz);
    float getCutFrequency() const;

    void setResonance(float res);
    float getResonance() const;

    void setBypass(bool isBypassed);
    bool getBypass() const;

    void process(juce::AudioBuffer<float>& buffer);

private:
    bool isInitialized;
    juce::dsp::ProcessSpec processSpec;
    struct StateVariableFilterSpec
    {
        std::atomic<bool> isBypassed;
    } svfSpec;
    juce::dsp::StateVariableTPTFilter<float> *pSVF;
};