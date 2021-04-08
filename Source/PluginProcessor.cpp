/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
G9SynthAudioProcessor::G9SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
       parameters(*this, nullptr, juce::Identifier("G9Synth"),
                  {
                       std::make_unique<juce::AudioParameterFloat>("SinOsc#shiftInCent", "SinOsc#PitchShift", -100.0f, 100.0f, 0.0f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#attack", "ADSR#Attack", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#decay", "ADSR#Decay", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#sustain", "ADSR#Sustain", 0.0f, 1.0f, 1.0f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#release", "ADSR#Release", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#time", "Delay#Time", 0.0f, 10.0f, 0.5f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#feedback", "Delay#Feedback", 0.0f, 1.0f, 0.5f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#mix", "Delay#Mix", 0.0f, 1.0f, 0.5f),
                  })
{
    parameters.addParameterListener("SinOsc#shiftInCent", this);
    parameters.addParameterListener("ADSR#attack", this);
    parameters.addParameterListener("ADSR#decay", this);
    parameters.addParameterListener("ADSR#sustain", this);
    parameters.addParameterListener("ADSR#release", this);
    parameters.addParameterListener("Delay#time", this);
    parameters.addParameterListener("Delay#feedback", this);
    parameters.addParameterListener("Delay#mix", this);
}

G9SynthAudioProcessor::~G9SynthAudioProcessor()
{
}

//==============================================================================
const juce::String G9SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool G9SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool G9SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool G9SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double G9SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int G9SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int G9SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void G9SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String G9SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void G9SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void G9SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sinWaveTable.initialize(4096); // the wave-table only initializes itself once
    sinOscillator.initialize(&sinWaveTable,0.f, sampleRate);
    adsr.setSampleRate(sampleRate);
    adsr.setParameters({
                    parameters.getParameter("ADSR#attack")->getValue(),
                    parameters.getParameter("ADSR#decay")->getValue(),
                    parameters.getParameter("ADSR#sustain")->getValue(),
                    parameters.getParameter("ADSR#release")->getValue(),
            });
    delay.initialize({sampleRate, static_cast<juce::uint32>(samplesPerBlock), 2}, 10);
    delay.setDelayTime(parameters.getParameter("Delay#time")->getValue());
    delay.setFeedback(parameters.getParameter("Delay#feedback")->getValue());
    delay.setMix(parameters.getParameter("Delay#mix")->getValue());
}

void G9SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    sinOscillator.reset();
    adsr.reset();
    delay.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool G9SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void G9SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto blockSize = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // parse the midi messages
    for (auto msg : midiMessages)
    {
        if (msg.getMessage().isNoteOn())
        {
            adsr.noteOn();
            currentMIDINote = msg.getMessage().getNoteNumber();
            sinOscillator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(currentMIDINote));
        }
        else if (msg.getMessage().isNoteOff())
        {
            if (msg.getMessage().getNoteNumber() == currentMIDINote)
                adsr.noteOff();
        }
    }

    // generate sin wave
    auto pp = buffer.getArrayOfWritePointers();
    for (auto i = 0; i < blockSize; ++i)
    {
        auto val = sinOscillator.getNextSample();
        for (auto c = 0; c < numChannels; ++c)
            pp[c][i] = val;
    }

    // ADSR
    adsr.applyEnvelopeToBuffer(buffer, 0, blockSize);

    // Delay
    delay.process(buffer);
}

//==============================================================================
bool G9SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* G9SynthAudioProcessor::createEditor()
{
    return new G9SynthAudioProcessorEditor (*this);
}

//==============================================================================
void G9SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void G9SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

void G9SynthAudioProcessor::parameterChanged (const juce::String &parameterID, float newValue)
{
    // Sin oscillator
    if (parameterID == "SinOsc#shiftInCent")
    {
        sinOscillator.shiftPitch(newValue);
    }
    // ADSR
    else if (parameterID == "ADSR#attack")
    {
        juce::ADSR::Parameters adsrParams = adsr.getParameters();
        adsrParams.attack = newValue;
        adsr.setParameters(adsrParams);
    }
    else if (parameterID == "ADSR#decay")
    {
        juce::ADSR::Parameters adsrParams = adsr.getParameters();
        adsrParams.decay = newValue;
        adsr.setParameters(adsrParams);
    }
    else if (parameterID == "ADSR#sustain")
    {
        juce::ADSR::Parameters adsrParams = adsr.getParameters();
        adsrParams.sustain = newValue;
        adsr.setParameters(adsrParams);
    }
    else if (parameterID == "ADSR#release")
    {
        juce::ADSR::Parameters adsrParams = adsr.getParameters();
        adsrParams.release = newValue;
        adsr.setParameters(adsrParams);
    }
    // Delay
    else if (parameterID == "Delay#time")
    {
        delay.setDelayTime(newValue);
    }
    else if (parameterID == "Delay#feedback")
    {
        delay.setFeedback(newValue);
    }
    else if (parameterID == "Delay#mix")
    {
        delay.setMix(newValue);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new G9SynthAudioProcessor();
}
