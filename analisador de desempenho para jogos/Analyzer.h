#pragma once

#include <chrono>
#include <cstdint>
#include <vector>

struct SampleWindow
{
    std::vector<double> samples;

    std::uint64_t sampleCount = 0;

    double elapsedMs = 0.0;
};

SampleWindow collectSamples(
    std::chrono::milliseconds windowDuration
);

void showSamples(
    const std::vector<double>& samples
);