/*
  ==============================================================================

    Filter.h
    Created: 19 Apr 2021 7:34:45pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include "SynthModule.h"

class StateVariableFilter : public SynthModule
{
public:
    enum class Type
    {
        lowPass,
        bandPass,
        highPass,
    };

    StateVariableFilter();
    ~StateVariableFilter() override;

    bool initialize(const juce::dsp::ProcessSpec& spec) override;
    void reset() override;
    void clear() override;
    void process(juce::AudioBuffer<float>& buffer) override;

    void setType(Type);
    Type getType() const;

    void setCutoffFrequency(float freqInHz);
    float getCutFrequency() const;

    void setResonance(float res);
    float getResonance() const;

    void setBypass(bool isBypassed);
    bool getBypass() const;

private:
    struct StateVariableFilterSpec
    {
        std::atomic<bool> isBypassed;
    } svfSpec;
    juce::dsp::StateVariableTPTFilter<float> *pSVF;
};