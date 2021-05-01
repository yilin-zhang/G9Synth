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
                       std::make_unique<juce::AudioParameterFloat>("SinOsc#gain", "SinOsc#Gain", 0.0f, 1.0f, 0.3f),
                       std::make_unique<juce::AudioParameterFloat>("SinOsc#shiftInCent", "SinOsc#PitchShift", -100.0f, 100.0f, 0.0f),
                       std::make_unique<juce::AudioParameterFloat>("SawOsc#gain", "SawOsc#Gain", 0.0f, 1.0f, 0.3f),
                       std::make_unique<juce::AudioParameterFloat>("SawOsc#shiftInCent", "SawOsc#PitchShift", -100.0f, 100.0f, 0.0f),
                       std::make_unique<juce::AudioParameterFloat>("SqrOsc#gain", "SqrOsc#Gain", 0.0f, 1.0f, 0.3f),
                       std::make_unique<juce::AudioParameterFloat>("SqrOsc#shiftInCent", "SqrOsc#PitchShift", -100.0f, 100.0f, 0.0f),
                       std::make_unique<juce::AudioParameterFloat>("Bitcrusher#depth", "Bitcrusher#Depth", 1.f, 32.f, 8.f),
                       std::make_unique<juce::AudioParameterFloat>("Bitcrusher#freq", "Bitcrusher#Freq", 200.f, 480000.f, 55600.f),
                       std::make_unique<juce::AudioParameterFloat>("Bitcrusher#mix", "Bitcrusher#Mix", 0.0f, 1.0f, 0.0f),
                       std::make_unique<juce::AudioParameterChoice>("SVF#type", "SVF#Type", juce::StringArray{"Lowpass", "Bandpass", "Highpass"}, 0),
                       std::make_unique<juce::AudioParameterFloat>("SVF#cutoff", "SVF#Cutoff", 50.f, 8000.0f, 1000.f),
                       std::make_unique<juce::AudioParameterFloat>("SVF#res", "SVF#Res", 0.01f, 1.f, 1/sqrt(2.0)),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#attack", "ADSR#Attack", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#decay", "ADSR#Decay", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#sustain", "ADSR#Sustain", 0.0f, 1.0f, 1.0f),
                       std::make_unique<juce::AudioParameterFloat>("ADSR#release", "ADSR#Release", 0.0f, 10.0f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("Vibrato#depth", "Vibrato#Depth", 0.0f, 0.2f, 0.1f),
                       std::make_unique<juce::AudioParameterFloat>("Vibrato#freq", "Vibrato#Freq", 0.0f, 10.0f, 5.f),
                       std::make_unique<juce::AudioParameterFloat>("Vibrato#mix", "Vibrato#Mix", 0.0f, 1.0f, 0.0f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#time", "Delay#Time", 0.0f, 10.0f, 0.5f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#feedback", "Delay#Feedback", 0.0f, 1.0f, 0.5f),
                       std::make_unique<juce::AudioParameterFloat>("Delay#mix", "Delay#Mix", 0.0f, 1.0f, 0.0f),
                       // TODO: The IR wav path is not stored
                       std::make_unique<juce::AudioParameterBool>("IR#bypassed", "IR#Bypassed", true),
                       std::make_unique<juce::AudioParameterFloat>("IR#mix", "Delay#Mix", 0.0f, 1.0f, 0.0f),
                  })
{
    parameters.addParameterListener("SinOsc#gain", this);
    parameters.addParameterListener("SinOsc#shiftInCent", this);
    parameters.addParameterListener("SawOsc#gain", this);
    parameters.addParameterListener("SawOsc#shiftInCent", this);
    parameters.addParameterListener("SqrOsc#gain", this);
    parameters.addParameterListener("SqrOsc#shiftInCent", this);
    parameters.addParameterListener("Bitcrusher#depth", this);
    parameters.addParameterListener("Bitcrusher#freq", this);
    parameters.addParameterListener("Bitcrusher#mix", this);
    parameters.addParameterListener("SVF#type", this);
    parameters.addParameterListener("SVF#cutoff", this);
    parameters.addParameterListener("SVF#res", this);
    parameters.addParameterListener("ADSR#attack", this);
    parameters.addParameterListener("ADSR#decay", this);
    parameters.addParameterListener("ADSR#sustain", this);
    parameters.addParameterListener("ADSR#release", this);
    parameters.addParameterListener("Vibrato#depth", this);
    parameters.addParameterListener("Vibrato#freq", this);
    parameters.addParameterListener("Vibrato#mix", this);
    parameters.addParameterListener("Delay#time", this);
    parameters.addParameterListener("Delay#feedback", this);
    parameters.addParameterListener("Delay#mix", this);
    parameters.addParameterListener("IR#bypassed", this);
    parameters.addParameterListener("IR#mix", this);
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
    juce::uint32 numChannels = getTotalNumOutputChannels();
    processSpec = {sampleRate, static_cast<juce::uint32>(samplesPerBlock), numChannels};

    sinWaveTable.initialize(4096); // the wave-table only initializes itself once
    sinOscillator.initialize(&sinWaveTable,0.f, sampleRate);

    sawWaveTable.initialize(4096);
    sawOscillator.initialize(&sawWaveTable,0.f, sampleRate);

    sqrWaveTable.initialize(4096);
    sqrOscillator.initialize(&sqrWaveTable,0.f, sampleRate);

    bitcrusher.initialize(processSpec);
    bitcrusher.setClockFrequency(parameters.getParameterAsValue("Bitcrusher#freq").getValue());
    bitcrusher.setBitDepth(parameters.getParameterAsValue("Bitcrusher#depth").getValue());
    bitcrusher.setMix(parameters.getParameterAsValue("Bitcrusher#mix").getValue());

    svf.initialize(processSpec);
    auto typeString = parameters.getParameter("SVF#type")->getCurrentValueAsText();
    if (typeString == "Lowpass")
        svf.setType(StateVariableFilter::Type::lowPass);
    else if (typeString == "Bandpass")
        svf.setType(StateVariableFilter::Type::bandPass);
    else if (typeString == "Highpass")
        svf.setType(StateVariableFilter::Type::highPass);
    svf.setCutoffFrequency(parameters.getParameterAsValue("SVF#cutoff").getValue());
    svf.setResonance(parameters.getParameterAsValue("SVF#res").getValue());

    adsr.setSampleRate(sampleRate);
    adsr.setParameters({
                    parameters.getParameterAsValue("ADSR#attack").getValue(),
                    parameters.getParameterAsValue("ADSR#decay").getValue(),
                    parameters.getParameterAsValue("ADSR#sustain").getValue(),
                    parameters.getParameterAsValue("ADSR#release").getValue(),
            });

    vibrato.initialize(processSpec, 0.2);
    vibrato.setDepth(parameters.getParameterAsValue("Vibrato#depth").getValue());
    vibrato.setFrequency(parameters.getParameterAsValue("Vibrato#freq").getValue());
    vibrato.setMix(parameters.getParameterAsValue("Vibrato#mix").getValue());

    delay.initialize(processSpec, 10);
    delay.setDelayTime(parameters.getParameterAsValue("Delay#time").getValue());
    delay.setFeedback(parameters.getParameterAsValue("Delay#feedback").getValue());
    delay.setMix(parameters.getParameterAsValue("Delay#mix").getValue());

    ir.initialize(processSpec);
    ir.setBypass(parameters.getParameterAsValue("IR#bypassed").getValue());
    ir.setMix(parameters.getParameterAsValue("IR#mix").getValue());
}

void G9SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    sinOscillator.reset();
    sawOscillator.reset();
    sqrOscillator.reset();
    bitcrusher.reset();
    vibrato.reset();
    svf.reset();
    adsr.reset();
    delay.reset();
    ir.reset();

    processSpec = {0.0, 0, 0};
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
            sawOscillator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(currentMIDINote));
            sqrOscillator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(currentMIDINote));
        }
        else if (msg.getMessage().isNoteOff())
        {
            if (msg.getMessage().getNoteNumber() == currentMIDINote)
                adsr.noteOff();
        }
    }

    // Oscillators
    auto pp = buffer.getArrayOfWritePointers();
    for (auto i = 0; i < blockSize; ++i)
    {
        auto val = sinOscillator.getNextSample() +
                   sawOscillator.getNextSample() +
                   sqrOscillator.getNextSample();
        for (auto c = 0; c < numChannels; ++c)
            pp[c][i] = val;
    }

    // split the buffer into smaller ones if it's larger than the expected size
    int startSample = 0;
    while (startSample < blockSize - 1)
    {
        int smallerSize = blockSize - startSample <= processSpec.maximumBlockSize ?
                          blockSize : processSpec.maximumBlockSize;
        juce::AudioBuffer<float> smallerBuffer (pp, numChannels, startSample, smallerSize);

        svf.process(smallerBuffer);
        adsr.applyEnvelopeToBuffer(smallerBuffer, 0, blockSize);
        vibrato.process(smallerBuffer);
        delay.process(smallerBuffer);
        ir.process(smallerBuffer);
        bitcrusher.process(smallerBuffer);

        startSample += smallerSize;
    }
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
    // Oscillators
    if (parameterID == "SinOsc#gain")
    {
        sinOscillator.setGain(newValue);
    }
    else if (parameterID == "SinOsc#shiftInCent")
    {
        sinOscillator.shiftPitch(newValue);
    }
    else if (parameterID == "SawOsc#gain")
    {
        sawOscillator.setGain(newValue);
    }
    else if (parameterID == "SawOsc#shiftInCent")
    {
        sawOscillator.shiftPitch(newValue);
    }
    else if (parameterID == "SqrOsc#gain")
    {
        sqrOscillator.setGain(newValue);
    }
    else if (parameterID == "SqrOsc#shiftInCent")
    {
        sqrOscillator.shiftPitch(newValue);
    }
    // Bitcrusher
    else if (parameterID == "Bitcrusher#depth")
    {
        bitcrusher.setBitDepth(newValue);
    }
    else if (parameterID == "Bitcrusher#freq")
    {
        bitcrusher.setClockFrequency(newValue);
    }
    else if (parameterID == "Bitcrusher#mix")
    {
        bitcrusher.setMix(newValue);
    }
    // SVF
    else if (parameterID == "SVF#type")
    {
        auto typeString = parameters.getParameter("SVF#type")->getCurrentValueAsText();

        if (typeString == "Lowpass")
            svf.setType(StateVariableFilter::Type::lowPass);
        else if (typeString == "Bandpass")
            svf.setType(StateVariableFilter::Type::bandPass);
        else if (typeString == "Highpass")
            svf.setType(StateVariableFilter::Type::highPass);
    }
    else if (parameterID == "SVF#cutoff")
    {
        svf.setCutoffFrequency(newValue);
    }
    else if (parameterID == "SVF#res")
    {
        svf.setResonance(newValue);
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
    // Vibrato
    else if (parameterID == "Vibrato#depth")
    {
        vibrato.setDepth(newValue);
    }
    else if (parameterID == "Vibrato#freq")
    {
        vibrato.setFrequency(newValue);
    }
    else if (parameterID == "Vibrato#mix")
    {
        vibrato.setMix(newValue);
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
    // IR
    else if (parameterID == "IR#bypassed")
    {
        DBG(newValue);
        ir.setBypass(static_cast<bool>(newValue));
    }
    else if (parameterID == "IR#mix")
    {
        ir.setMix(newValue);
    }
}

juce::AudioProcessorValueTreeState& G9SynthAudioProcessor::getValueTreeState()
{
    return parameters;
}

void G9SynthAudioProcessor::loadIR(const juce::String &path)
{
    ir.loadImpulseResponse(path);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new G9SynthAudioProcessor();
}
