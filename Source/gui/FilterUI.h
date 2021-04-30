/*
  ==============================================================================

    FilterUI.h
    Created: 29 Apr 2021 3:19:04pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class FilterUI  : public juce::Component
{
public:
    explicit FilterUI(G9SynthAudioProcessor&);
    ~FilterUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    G9SynthAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;

    juce::ComboBox filterType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    juce::Slider cutoff;
    juce::Label cutoffLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    juce::Slider res;
    juce::Label resLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterUI)
};
