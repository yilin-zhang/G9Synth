/*
  ==============================================================================

    WaveTable.cpp
    Created: 28 Mar 2021 10:30:40am
    Author:  Yilin Zhang

  ==============================================================================
*/

#include "WaveTable.h"

// ========================================
// WaveTable
// ========================================

WaveTable::WaveTable() : isInitialized(false) {}

void WaveTable::initialize(int tableSize)
{
    if (isInitialized)
        return;

    table.setSize(1, tableSize);
    isInitialized = true;
}

float WaveTable::getSample(float phase) const
{
    if (!isInitialized)
        return 0.f;

    auto tableSize = table.getNumSamples();
    auto tablePointer = getTablePointer();

    // wrap the phase
    float wrappedPhase = phase - floor(phase);
    float index = wrappedPhase * static_cast<float>(tableSize);
    int indexFl = floor(index); float valFl = tablePointer[indexFl];
    int indexCe = ceil(index); indexCe = indexCe % tableSize; float valCe = tablePointer[indexCe];

    // linear interpolation for simplicity
    float value = valFl + (index - static_cast<float>(indexFl)) * (valCe - valFl);
    return value;
}

float WaveTable::getSample(const juce::dsp::Phase<float>& phase) const
{
    float fPhase = phase.phase / (2.f * juce::float_Pi);
    return getSample(fPhase);
}

const float* WaveTable::getTablePointer() const
{
    return table.getReadPointer(0);
}

int WaveTable::getSize() const
{
    return table.getNumSamples();
}

// ========================================
// SinWaveTable
// ========================================

void SinWaveTable::initialize(int tableSize)
{
    WaveTable::initialize(tableSize);
    auto writePointer = table.getWritePointer(0);
    for (int i=0; i<tableSize; ++i)
        writePointer[i] = static_cast<float>(sin(2 * juce::float_Pi / tableSize * i));
}

void SawWaveTable::initialize(int tableSize)
{
    WaveTable::initialize(tableSize);
    // TODO: fill the table
}

void SqrWaveTable::initialize(int tableSize)
{
    WaveTable::initialize(tableSize);
    // TODO: fill the table
}

void EditableWaveTable::editTable(int startSample, const float* source, int numSamples)
{
    table.copyFrom(0, startSample, source, numSamples);
}

