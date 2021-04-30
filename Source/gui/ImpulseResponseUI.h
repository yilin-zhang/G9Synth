/*
  ==============================================================================

    ImpulseResponseUI.h
    Created: 30 Apr 2021 9:53:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class ImpulseResponseUI  : public juce::Component
{
public:
    explicit ImpulseResponseUI(G9SynthAudioProcessor&);
    ~ImpulseResponseUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void loadIRButtonClicked();

    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    juce::TextButton loadIR;

    juce::ToggleButton bypassed;
    juce::Label bypassedLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedAttachment;

    juce::Slider mix;
    juce::Label mixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImpulseResponseUI)
};
