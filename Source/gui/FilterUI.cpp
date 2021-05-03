/*
  ==============================================================================

    FilterUI.cpp
    Created: 29 Apr 2021 3:19:04pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterUI.h"

//==============================================================================
FilterUI::FilterUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
cutoff {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
res {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(225, 250);

    addAndMakeVisible(filterType);
    filterType.addItem("Lowpass", 1);
    filterType.addItem("Bandpass", 2);
    filterType.addItem("Highpass", 3);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(parameters, "SVF#type", filterType);

    addAndMakeVisible(cutoff);
    cutoff.setTextValueSuffix(" Hz");
    cutoffLabel.setText("Cutoff", juce::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoff, false);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SVF#cutoff", cutoff);

    addAndMakeVisible(res);
    resLabel.setText("Res", juce::dontSendNotification);
    resLabel.attachToComponent(&res, false);
    resAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "SVF#res", res);

    addAndMakeVisible(bypassed);
    bypassed.setToggleState(false, juce::dontSendNotification);
    bypassedLabel.setText("Bypass", juce::dontSendNotification);
    bypassedLabel.attachToComponent(&bypassed, false);
    bypassedAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, "SVF#bypassed", bypassed);
}

FilterUI::~FilterUI() = default;

void FilterUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterUI::resized()
{
    juce::Rectangle<int> cutoffSize (0, 0, 100, 100);
    juce::Rectangle<int> resSize (0, 0, 70, 70);
    juce::Rectangle<int> toggleSize (0, 0, 50, 20);

    filterType.setBounds(45, 45, 120, 30);
    bypassed.setBounds(20, 45, toggleSize.getWidth(), toggleSize.getHeight());
    cutoff.setBounds(20, 120, cutoffSize.getWidth(), cutoffSize.getHeight());
    res.setBounds(120, 130, resSize.getWidth(), resSize.getHeight());
}
