/*
  ==============================================================================

    GainUI.h
    Created: 4 May 2021 5:51:59pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class GainUI  : public juce::Component
{
public:
    GainUI(G9SynthAudioProcessor&);
    ~GainUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    juce::Slider gain;
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainUI)
};
