/*
  ==============================================================================

    Filter.cpp
    Created: 19 Apr 2021 7:34:45pm
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "Filter.h"

StateVariableFilter::StateVariableFilter():isInitialized(false),
processSpec({0.0, 0, 0}), pSVF(nullptr)
{}

StateVariableFilter::~StateVariableFilter()
{
    reset();
}

bool StateVariableFilter::initialize(const juce::dsp::ProcessSpec &spec)
{
    reset();

    processSpec = spec;

    // 1. allocate memory
    pSVF = new juce::dsp::StateVariableTPTFilter<float>;
    pSVF->prepare(spec);

    isInitialized = true;

    return true;
}

void StateVariableFilter::reset()
{
    if (!isInitialized)
        return;

    clear();

    // release memory
    delete pSVF;
    pSVF = nullptr;

    processSpec = {0.0, 0, 0};

    isInitialized = false;
}

void StateVariableFilter::clear()
{
    if (!isInitialized)
        return;

    pSVF->reset();
}

void StateVariableFilter::setType(Type type)
{
    if (!isInitialized)
        return;

    switch (type)
    {
        case Type::lowPass:
            pSVF->setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case Type::bandPass:
            pSVF->setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case Type::highPass:
            pSVF->setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
}

StateVariableFilter::Type StateVariableFilter::getType() const
{
    if (!isInitialized)
        return Type::lowPass;

    auto internalType = pSVF->getType();

    switch(internalType)
    {
        case juce::dsp::StateVariableTPTFilterType::lowpass:
            return Type::lowPass;
        case juce::dsp::StateVariableTPTFilterType::bandpass:
            return Type::bandPass;
        case juce::dsp::StateVariableTPTFilterType::highpass:
            return Type::highPass;
    }
}

void StateVariableFilter::setCutoffFrequency(float freqInHz)
{
    if (!isInitialized)
        return;

    pSVF->setCutoffFrequency(freqInHz);
}

float StateVariableFilter::getCutFrequency() const
{
    if (!isInitialized)
        return 0.f;

    return pSVF->getCutoffFrequency();
}

void StateVariableFilter::setResonance(float res)
{
    if (!isInitialized)
        return;

    pSVF->setResonance(res);
}

float StateVariableFilter::getResonance() const
{
    if (!isInitialized)
        return 0.f;

    return pSVF->getResonance();
}

void StateVariableFilter::process(juce::AudioBuffer<float>& buffer)
{
    if (!isInitialized)
        return;

//    auto numSamples = buffer.getNumSamples();
//    auto ppBuffer = buffer.getArrayOfWritePointers();
//    auto numChannels = processSpec.numChannels < buffer.getNumChannels() ? processSpec.numChannels :
//                                                                           buffer.getNumChannels();

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    pSVF->process(context);
//    for (int c=0; c<numChannels; ++c)
//    {
//        for (int i=0; i<numSamples; ++i)
//        {
//            pSVF->processSample(c, ppBuffer[c][i]);
//        }
//    }
}



