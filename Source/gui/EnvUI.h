/*
  ==============================================================================

    EnvUI.h
    Created: 29 Apr 2021 4:38:31pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class EnvUI  : public juce::Component
{
public:
    explicit EnvUI (G9SynthAudioProcessor&);
    ~EnvUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    juce::Slider attack;
    juce::Label attackLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;

    juce::Slider decay;
    juce::Label decayLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    // Saw
    juce::Slider sustain;
    juce::Label sustainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;

    juce::Slider release;
    juce::Label releaseLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvUI)
};
