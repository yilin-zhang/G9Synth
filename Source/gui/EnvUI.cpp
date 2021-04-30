/*
  ==============================================================================

    EnvUI.cpp
    Created: 29 Apr 2021 4:38:31pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvUI.h"

//==============================================================================
EnvUI::EnvUI(G9SynthAudioProcessor& p) : processor(p), parameters(p.getValueTreeState()),
attack {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
decay {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
sustain {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow},
release {juce::Slider::LinearVertical, juce::Slider::TextBoxBelow}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(290, 250);

    addAndMakeVisible(attack);
    attack.setTextValueSuffix(" s");
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.attachToComponent(&attack, false);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "ADSR#attack", attack);

    addAndMakeVisible(decay);
    decay.setTextValueSuffix(" s");
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.attachToComponent(&decay, false);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "ADSR#decay", decay);

    addAndMakeVisible(sustain);
    sustain.setTextValueSuffix(" s");
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sustain, false);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "ADSR#sustain", sustain);

    addAndMakeVisible(release);
    release.setTextValueSuffix(" s");
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.attachToComponent(&release, false);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, "ADSR#release", release);
}

EnvUI::~EnvUI() = default;

void EnvUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Env", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area (0, 25, getWidth(), getHeight()-25);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void EnvUI::resized()
{
    juce::Rectangle<int> barSize (0, 0, 50, 160);

    attack.setBounds(17, 60, barSize.getWidth(), barSize.getHeight());
    decay.setBounds(17 + (20+barSize.getWidth()), 60, barSize.getWidth(), barSize.getHeight());
    sustain.setBounds(17 + 2 * (20+barSize.getWidth()), 60, barSize.getWidth(), barSize.getHeight());
    release.setBounds(17 + 3 * (20+barSize.getWidth()), 60, barSize.getWidth(), barSize.getHeight());
}
