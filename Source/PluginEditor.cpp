/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
G9SynthAudioProcessorEditor::G9SynthAudioProcessorEditor (G9SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), parameters(p.getValueTreeState()),
      oscillatorUI(p), filterUI(p), envUI(p), vibratoUI(p), delayUI(p), irUI(p), bitcrusherUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(false, false);
    setSize (oscillatorUI.getWidth()+filterUI.getWidth()+envUI.getWidth(),
             oscillatorUI.getHeight()+vibratoUI.getHeight());

    addAndMakeVisible(oscillatorUI);
    addAndMakeVisible(filterUI);
    addAndMakeVisible(envUI);
    addAndMakeVisible(vibratoUI);
    addAndMakeVisible(delayUI);
    addAndMakeVisible(irUI);
    addAndMakeVisible(bitcrusherUI);
}

G9SynthAudioProcessorEditor::~G9SynthAudioProcessorEditor()
{
}

//==============================================================================
void G9SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void G9SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
//    juce::Rectangle<int> area = getLocalBounds();
//    const int componentWidth = 200;
//    const int componentHeight = 200;

    oscillatorUI.setBounds(0, 0, oscillatorUI.getWidth(), oscillatorUI.getHeight());
    filterUI.setBounds(oscillatorUI.getWidth(), 0, filterUI.getWidth(), filterUI.getHeight());
    envUI.setBounds(oscillatorUI.getWidth()+filterUI.getWidth(), 0, envUI.getWidth(), envUI.getHeight());
    vibratoUI.setBounds(0, oscillatorUI.getHeight(), vibratoUI.getWidth(), vibratoUI.getHeight());
    delayUI.setBounds(vibratoUI.getWidth(), oscillatorUI.getHeight(), delayUI.getWidth(), delayUI.getHeight());
    irUI.setBounds(vibratoUI.getWidth()+delayUI.getWidth(), oscillatorUI.getHeight(), irUI.getWidth(), irUI.getHeight());
    bitcrusherUI.setBounds(vibratoUI.getWidth()+delayUI.getWidth()+irUI.getWidth(), oscillatorUI.getHeight(), bitcrusherUI.getWidth(), bitcrusherUI.getHeight());
}
