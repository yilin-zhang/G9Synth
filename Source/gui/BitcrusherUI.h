/*
  ==============================================================================

    BitcrusherUI.h
    Created: 1 May 2021 3:56:07pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class BitcrusherUI  : public juce::Component
{
public:
    explicit BitcrusherUI(G9SynthAudioProcessor&);
    ~BitcrusherUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    juce::Slider freq;
    juce::Label freqLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;

    juce::Slider depth;
    juce::Label depthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;

    juce::Slider mix;
    juce::Label mixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitcrusherUI)
};
