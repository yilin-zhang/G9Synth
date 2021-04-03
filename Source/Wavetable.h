/*
  ==============================================================================

    WaveTable.h
    Created: 28 Mar 2021 10:30:40am
    Author:  Yilin Zhang

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include<juce_dsp/maths/juce_Phase.h>
// https://docs.juce.com/master/tutorial_wavetable_synth.html

class WaveTable
{
public:
    WaveTable();
    virtual ~WaveTable() = default;
    virtual void initialize(int tableSize);
    float getSample(float phase) const;
    float getSample(const juce::dsp::Phase<float>& phase) const;
    const float* getTablePointer() const;
    int getSize() const;
protected:
    bool isInitialized;
    juce::AudioBuffer<float> table;
};

class SinWaveTable : public WaveTable
{
public:
    SinWaveTable() = default;
    ~SinWaveTable() override = default;
    void initialize(int tableSize) override;
};

class SawWaveTable : public WaveTable
{
public:
    SawWaveTable() = default;
    ~SawWaveTable() override = default;
    void initialize(int tableSize) override;
};

class SqrWaveTable : public WaveTable
{
public:
    SqrWaveTable() = default;
    ~SqrWaveTable() override = default;
    void initialize(int tableSize) override;
};

class EditableWaveTable : public WaveTable
{
public:
    EditableWaveTable() = default;
    ~EditableWaveTable() override = default;
    void editTable(int startSample, const float* source, int numSamples);
};