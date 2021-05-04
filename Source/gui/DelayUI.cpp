/*
  ==============================================================================

    DelayUI.cpp
    Created: 29 Apr 2021 5:16:01pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayUI.h"

//==============================================================================
DelayUI::DelayUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
time {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
feedback {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow},
mix {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 250);

    addAndMakeVisible(time);
    timeLabel.setText("Time", juce::dontSendNotification);
    timeLabel.attachToComponent(&time, false);
    timeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Delay#time", time);

    addAndMakeVisible(feedback);
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent(&feedback, false);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Delay#feedback", feedback);

    addAndMakeVisible(mix);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mix, false);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "Delay#mix", mix);
}

DelayUI::~DelayUI() = default;

void DelayUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Delay", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::blueviolet);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void DelayUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> knobSize (0, 0, 80, 80);

    time.setBounds(25, 45, knobSize.getWidth(), knobSize.getHeight());
    feedback.setBounds(25 + knobSize.getWidth(), 45, knobSize.getWidth(), knobSize.getHeight());
    mix.setBounds(55, 45+(30+knobSize.getHeight()), knobSize.getWidth(), knobSize.getHeight());
}
