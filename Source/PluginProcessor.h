/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "dsp/Oscillator.h"
#include "dsp/RingMod.h"
#include "dsp/Filter.h"
#include "dsp/Delay.h"
#include "dsp/Vibrato.h"
#include "dsp/ImpulseResponse.h"
#include "dsp/Bitcrusher.h"

//==============================================================================
/**
*/
class G9SynthAudioProcessor  : public juce::AudioProcessor,
                               public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    G9SynthAudioProcessor();
    ~G9SynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void parameterChanged (const juce::String &parameterID, float newValue) override;

    //==============================================================================
    juce::AudioProcessorValueTreeState& getValueTreeState();
    void loadIR(const juce::String &path);

private:
    juce::AudioProcessorValueTreeState parameters;
    juce::dsp::ProcessSpec processSpec;

    SinWaveTable sinWaveTable;
    WaveTableOscillator sinOscillator;
    SawWaveTable sawWaveTable;
    WaveTableOscillator sawOscillator;
    SqrWaveTable sqrWaveTable;
    WaveTableOscillator sqrOscillator;

    RingMod ringmod;
    Vibrato vibrato;
    Bitcrusher bitcrusher;
    StateVariableFilter svf;
    juce::ADSR adsr;
    Delay delay;
    ImpulseResponse ir;

    std::atomic<float> gain;

    int currentMIDINote;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (G9SynthAudioProcessor)
};
