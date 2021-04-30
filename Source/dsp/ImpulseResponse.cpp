/*
  ==============================================================================

    ImpulseResponse.cpp
    Created: 29 Apr 2021 10:11:25pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "ImpulseResponse.h"

ImpulseResponse::ImpulseResponse() : isInitialized(false),
                                     processSpec({0, 0, 0}),
                                     impulseResponseSpec({true, 0.f}) {}

ImpulseResponse::~ImpulseResponse() {}

bool ImpulseResponse::initialize(const juce::dsp::ProcessSpec &spec)
{
    impulseResponseSpec.isBypassed = true;
    convolution.prepare(spec);
    isInitialized = true;

    return true;
}

bool ImpulseResponse::initialize(const juce::dsp::ProcessSpec &spec, const juce::String &pathToWav)
{
    if (!loadImpulseResponse(pathToWav))
        return false;

    convolution.prepare(spec);
    impulseResponseSpec.isBypassed = false;
    isInitialized = true;

    return true;
}

bool ImpulseResponse::getInitialized() const
{
    return isInitialized;
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

    impulseResponseSpec = {true, 0.f};
    // NOTE: will this make convolution prepare again?
    convolution.reset();

    isInitialized = false;
}

void ImpulseResponse::clear()
{
    if (!isInitialized)
        return;

    // NOTE: will this make convolution prepare again?
    convolution.reset();
}

void ImpulseResponse::process(juce::AudioBuffer<float> &buffer)
{
    if (impulseResponseSpec.isBypassed || !isInitialized)
        return;

    float mix = impulseResponseSpec.mix;

    dryBuffer.makeCopyOf(buffer);
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    convolution.process(context);

    dryBuffer.applyGain(1.f - mix);
    buffer.applyGain(mix);

    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
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
    impulseResponseSpec.mix = value;
}

float ImpulseResponse::getMix() const
{
    return impulseResponseSpec.mix;
}