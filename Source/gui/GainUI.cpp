/*
  ==============================================================================

    GainUI.cpp
    Created: 4 May 2021 5:51:59pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainUI.h"

//==============================================================================
GainUI::GainUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
gain {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(60, 250);

    addAndMakeVisible(gain);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gain, false);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "gain", gain);
}

GainUI::~GainUI() = default;

void GainUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Gain", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void GainUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> knobSize (0, 0, 70, 70);
    gain.setBounds(2, 25+(30+knobSize.getHeight()), knobSize.getWidth(), knobSize.getHeight());
}
