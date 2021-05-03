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

    /**
     * Sets the filter type
     */
    void setType(Type);

    /**
     * Returns the filter type
     * @return
     */
    Type getType() const;

    /**
     * Sets the cutoff frequency
     * @param freqInHz
     */
    void setCutoffFrequency(float freqInHz);

    /**
     * Returns the cutoff frequency
     * @return
     */
    float getCutFrequency() const;

    /**
     * Sets the resonance
     * @param res
     */
    void setResonance(float res);

    /**
     * Returns the resonance
     * @return
     */
    float getResonance() const;

    /**
     * Sets the bypass state
     * @param isBypassed
     */
    void setBypass(bool isBypassed);

    /**
     * Returns the bypass state
     * @return
     */
    bool getBypass() const;

private:
    struct StateVariableFilterSpec
    {
        std::atomic<bool> isBypassed;
    } svfSpec;
    juce::dsp::StateVariableTPTFilter<float> *pSVF;
};