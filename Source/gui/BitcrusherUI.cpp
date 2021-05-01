/*
  ==============================================================================

    BitcrusherUI.cpp
    Created: 1 May 2021 3:56:07pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BitcrusherUI.h"

//==============================================================================
BitcrusherUI::BitcrusherUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
                                                       freq {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
                                                       depth {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
                                                       mix {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 250);

    addAndMakeVisible(freq);
    freqLabel.setText("Clock Freq", juce::dontSendNotification);
    freqLabel.attachToComponent(&freq, false);
    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Bitcrusher#freq", freq);

    addAndMakeVisible(depth);
    depthLabel.setText("Bit Depth", juce::dontSendNotification);
    depthLabel.attachToComponent(&depth, false);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Bitcrusher#depth", depth);

    addAndMakeVisible(mix);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mix, false);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Bitcrusher#mix", mix);
}

BitcrusherUI::~BitcrusherUI() = default;

void BitcrusherUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Bitcrusher", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void BitcrusherUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> knobSize (0, 0, 80, 80);

    freq.setBounds(25, 45, knobSize.getWidth(), knobSize.getHeight());
    depth.setBounds(25 + knobSize.getWidth(), 45, knobSize.getWidth(), knobSize.getHeight());
    mix.setBounds(55, 45+(30+knobSize.getHeight()), knobSize.getWidth(), knobSize.getHeight());
}
