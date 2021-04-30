/*
  ==============================================================================

    ImpulseResponseUI.cpp
    Created: 30 Apr 2021 9:53:11am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ImpulseResponseUI.h"

//==============================================================================
ImpulseResponseUI::ImpulseResponseUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
mix {juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(150, 250);

    addAndMakeVisible(loadIR);
    loadIR.onClick = [this] {loadIRButtonClicked(); };

    addAndMakeVisible(bypassed);
    bypassed.setToggleState(false, juce::dontSendNotification);
    bypassedLabel.setText("Bypass", juce::dontSendNotification);
    bypassedLabel.attachToComponent(&bypassed, false);
    bypassedAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, "IR#bypassed", bypassed);


    addAndMakeVisible(mix);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mix, false);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "IR#mix", mix);

    // TODO: since the UI is handling the IR loading for now, it's UI that decides whether the toggle should be enabled
}

ImpulseResponseUI::~ImpulseResponseUI() = default;

void ImpulseResponseUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("IR", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void ImpulseResponseUI::resized()
{
    juce::Rectangle<int> knobSize (0, 0, 80, 80);
    juce::Rectangle<int> toggleSize (0, 0, 50, 20);
    juce::Rectangle<int> buttonSize (0, 0, 80, 40);

    bypassed.setBounds(20, 45, toggleSize.getWidth(), toggleSize.getHeight());
    loadIR.setBounds(25, 55+toggleSize.getHeight(), buttonSize.getWidth(), buttonSize.getHeight());
    loadIR.setButtonText("Load IR");
    mix.setBounds(35, 55+(toggleSize.getHeight()+knobSize.getHeight()), knobSize.getWidth(), knobSize.getHeight());
}

void ImpulseResponseUI::loadIRButtonClicked()
{
    juce::FileChooser fileChooser("Select the path", {});
    if (fileChooser.browseForFileToOpen())
        processor.loadIR(fileChooser.getResult().getFullPathName());
}