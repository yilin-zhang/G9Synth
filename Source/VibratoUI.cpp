/*
  ==============================================================================

    VibratoUI.cpp
    Created: 29 Apr 2021 4:57:41pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VibratoUI.h"

//==============================================================================
VibratoUI::VibratoUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
depth {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
freq {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
mix {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 250);

    addAndMakeVisible(depth);
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.attachToComponent(&depth, false);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Vibrato#depth", depth);

    addAndMakeVisible(freq);
    freqLabel.setText("Freq", juce::dontSendNotification);
    freqLabel.attachToComponent(&freq, false);
    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Vibrato#freq", freq);

    addAndMakeVisible(mix);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mix, false);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Vibrato#mix", mix);
}

VibratoUI::~VibratoUI() = default;

void VibratoUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Vibrato", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void VibratoUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> knobSize (0, 0, 80, 80);

    depth.setBounds(25, 45, knobSize.getWidth(), knobSize.getHeight());
    freq.setBounds(25 + knobSize.getWidth(), 45, knobSize.getWidth(), knobSize.getHeight());
    mix.setBounds(50, 45+(30+knobSize.getHeight()), knobSize.getWidth(), knobSize.getHeight());
}
