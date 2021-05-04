/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "gui/OscillatorUI.h"
#include "gui/FilterUI.h"
#include "gui/EnvUI.h"
#include "gui/VibratoUI.h"
#include "gui/DelayUI.h"
#include "gui/ImpulseResponseUI.h"
#include "gui/BitcrusherUI.h"
#include "gui/GainUI.h"

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
    ImpulseResponseUI irUI;
    BitcrusherUI bitcrusherUI;
    GainUI gainUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (G9SynthAudioProcessorEditor)
};
