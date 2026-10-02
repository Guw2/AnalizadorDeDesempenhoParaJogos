#pragma once

#include <cstdint>
#include <vector>

struct Metrics
{
    double avgMs = 0.0;
    double minMs = 0.0;
    double maxMs = 0.0;
    double desApx = 0.0;

    double samplesPerSecond = 0.0;
};

Metrics calculateMetrics(
    const std::vector<double>& samples,
    std::uint64_t sampleCount,
    double elapsedMs
);