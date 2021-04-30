/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "OscillatorUI.h"
#include "FilterUI.h"
#include "EnvUI.h"
#include "VibratoUI.h"
#include "DelayUI.h"

//==============================================================================
/**
*/
class G9SynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    G9SynthAudioProcessorEditor (G9SynthAudioProcessor&);
    ~G9SynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    G9SynthAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& parameters;

    OscillatorUI oscillatorUI;
    FilterUI filterUI;
    EnvUI envUI;
    VibratoUI vibratoUI;
    DelayUI delayUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (G9SynthAudioProcessorEditor)
};
