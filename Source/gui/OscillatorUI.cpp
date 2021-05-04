/*
  ==============================================================================

    OscillatorUI.cpp
    Created: 29 Apr 2021 11:41:04am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "OscillatorUI.h"

#include <memory>

OscillatorUI::OscillatorUI(G9SynthAudioProcessor &p) : processor(p), parameters(p.getValueTreeState()),
sinGain {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
sinShiftInCent {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
sawGain {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
sawShiftInCent {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
sqrGain {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
sqrShiftInCent {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
modFreq {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
modMix {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    setSize(300, 250);

    addAndMakeVisible(sinGain);
    sinGainLabel.setText("Sine", juce::dontSendNotification);
    sinGainLabel.attachToComponent(&sinGain, false);
    sinGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SinOsc#gain", sinGain);

    addAndMakeVisible(sinShiftInCent);
    sinShiftInCent.setTextValueSuffix(" ct");
    sinShiftInCentLabel.setText("Pitch Shift", juce::dontSendNotification);
    sinShiftInCentLabel.attachToComponent(&sinShiftInCent, false);
    sinShiftInCentAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SinOsc#shiftInCent", sinShiftInCent);

    addAndMakeVisible(sawGain);
    sawGainLabel.setText("Saw", juce::dontSendNotification);
    sawGainLabel.attachToComponent(&sawGain, false);
    sawGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SawOsc#gain", sawGain);

    addAndMakeVisible(sawShiftInCent);
    sawShiftInCent.setTextValueSuffix(" ct");
    sawShiftInCentLabel.setText("Pitch Shift", juce::dontSendNotification);
    sawShiftInCentLabel.attachToComponent(&sawShiftInCent, false);
    sawShiftInCentAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SawOsc#shiftInCent", sawShiftInCent);

    addAndMakeVisible(sqrGain);
    sqrGainLabel.setText("Square", juce::dontSendNotification);
    sqrGainLabel.attachToComponent(&sqrGain, false);
    sqrGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SqrOsc#gain", sqrGain);

    addAndMakeVisible(sqrShiftInCent);
    sqrShiftInCent.setTextValueSuffix(" ct");
    sqrShiftInCentLabel.setText("Pitch Shift", juce::dontSendNotification);
    sqrShiftInCentLabel.attachToComponent(&sqrShiftInCent, false);
    sqrShiftInCentAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SqrOsc#shiftInCent", sqrShiftInCent);

    addAndMakeVisible(modFreq);
    modFreqLabel.setText("Mod", juce::dontSendNotification);
    modFreqLabel.attachToComponent(&modFreq, false);
    modFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "RingMod#freq", modFreq);

    addAndMakeVisible(modMix);
    modMixLabel.setText("Mix", juce::dontSendNotification);
    modMixLabel.attachToComponent(&modMix, false);
    modMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "RingMod#mix", modMix);
}

OscillatorUI::~OscillatorUI() = default;

void OscillatorUI::paint(juce::Graphics &g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillators", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::red);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorUI::resized()
{
    juce::Rectangle<int> barSize (0, 0, 50, 100);
    juce::Rectangle<int> knobSize (0, 0, 70, 70);

    sinGain.setBounds(15, 45, barSize.getWidth(), barSize.getHeight());
    sawGain.setBounds(15 + (20+barSize.getWidth()), 45, barSize.getWidth(), barSize.getHeight());
    sqrGain.setBounds(15 + 2 * (20+barSize.getWidth()), 45, barSize.getWidth(), barSize.getHeight());

    sinShiftInCent.setBounds(7, 70+barSize.getHeight(), knobSize.getWidth(), knobSize.getHeight());
    sawShiftInCent.setBounds(7 + (20+barSize.getWidth()), 70+barSize.getHeight(), knobSize.getWidth(), knobSize.getHeight());
    sqrShiftInCent.setBounds(7 + 2*(20+barSize.getWidth()), 70+barSize.getHeight(), knobSize.getWidth(), knobSize.getHeight());

    modFreq.setBounds(15 + 3 * (20+barSize.getWidth()), 45, knobSize.getWidth(), knobSize.getHeight());
    modMix.setBounds(7 + 3 * (20+barSize.getWidth()), 70+barSize.getHeight(), knobSize.getWidth(), knobSize.getHeight());
}