/*
  ==============================================================================

    OscillatorUI.h
    Created: 29 Apr 2021 11:41:04am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginProcessor.h"

class OscillatorUI : public juce::Component
{
public:
    explicit OscillatorUI(G9SynthAudioProcessor&);
    ~OscillatorUI() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    // Sin
    juce::Slider sinGain;
    juce::Label sinGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sinGainAttachment;

    juce::Slider sinShiftInCent;
    juce::Label sinShiftInCentLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sinShiftInCentAttachment;

    // Saw
    juce::Slider sawGain;
    juce::Label sawGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sawGainAttachment;

    juce::Slider sawShiftInCent;
    juce::Label sawShiftInCentLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sawShiftInCentAttachment;

    // Sqr
    juce::Slider sqrGain;
    juce::Label sqrGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sqrGainAttachment;

    juce::Slider sqrShiftInCent;
    juce::Label sqrShiftInCentLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sqrShiftInCentAttachment;


};