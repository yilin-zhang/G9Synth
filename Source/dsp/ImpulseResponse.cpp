/*
  ==============================================================================

    ImpulseResponse.cpp
    Created: 29 Apr 2021 10:11:25pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "ImpulseResponse.h"

ImpulseResponse::ImpulseResponse() : SynthModule()
{
    impulseResponseSpec.isBypassed = true; impulseResponseSpec.mix = 0.f;
}

ImpulseResponse::~ImpulseResponse()
{
    reset();
}

bool ImpulseResponse::initialize(const juce::dsp::ProcessSpec &spec)
{
    if (!SynthModule::initialize(spec))
        return false;

    impulseResponseSpec.isBypassed = true;
    convolution.prepare(spec);
    dryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);

    return true;
}

bool ImpulseResponse::loadImpulseResponse(const juce::String &pathToWav)
{
    juce::File wav(pathToWav);

    // check if the file is valid
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    auto* reader = formatManager.createReaderFor (wav);
    if (!reader)
        return false;

    // get the number of channels and load the audio
    int numChannels = static_cast<int>(reader->numChannels);
    delete reader;
    auto isStereo = numChannels >= 2 ? juce::dsp::Convolution::Stereo::yes :
                    juce::dsp::Convolution::Stereo::no;
    convolution.loadImpulseResponse(wav, isStereo, juce::dsp::Convolution::Trim::no, 0);

    return true;
}

void ImpulseResponse::reset()
{
    if (!isInitialized)
        return;

    clear();

    processSpec = {0.0, 0, 0};
    impulseResponseSpec.isBypassed = true; impulseResponseSpec.mix = 0.f;

    isInitialized = false;
}

void ImpulseResponse::clear()
{
    if (!isInitialized)
        return;

    // NOTE: will this make convolution prepare again?
    convolution.reset();
    dryBuffer.clear();
}

void ImpulseResponse::process(juce::AudioBuffer<float> &buffer)
{
    if (impulseResponseSpec.isBypassed)
        return;

    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    float mix = impulseResponseSpec.mix;

    for (int c = 0; c < numChannels; ++c)
        dryBuffer.copyFrom(c, 0, buffer, c, 0, numSamples);

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    convolution.process(context);

    dryBuffer.applyGain(1.f - mix);
    buffer.applyGain(mix);

    for (int c = 0; c < numChannels; ++c)
        buffer.addFrom(c, 0, dryBuffer, c, 0, numSamples);
}

void ImpulseResponse::setBypass(bool isBypassed)
{
    impulseResponseSpec.isBypassed = isBypassed;
}

bool ImpulseResponse::getBypassed() const
{
    return impulseResponseSpec.isBypassed;
}

void ImpulseResponse::setMix(float value)
{
    if (value > 1.f)
        value = 1.f;
    else if (value < 0.f)
        value = 0.f;

    impulseResponseSpec.mix = value;
}

float ImpulseResponse::getMix() const
{
    return impulseResponseSpec.mix;
}