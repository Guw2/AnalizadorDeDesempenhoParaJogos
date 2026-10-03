#include "Metrics.h"

#include <algorithm>
#include <cmath>
#include <numeric>

Metrics calculateMetrics(const SampleWindow& window)
{
    if (window.samplesMs.empty() || window.elapsedMs <= 0.0)
    {
        return {};
    }

    const double sum =
        std::accumulate(
            window.samplesMs.begin(),
            window.samplesMs.end(),
            0.0
        );

    const double average =
        sum / window.samplesMs.size();

    const double minimum =
        *std::min_element(
            window.samplesMs.begin(),
            window.samplesMs.end()
        );

    const double maximum =
        *std::max_element(
            window.samplesMs.begin(),
            window.samplesMs.end()
        );

    double squaredDifferenceSum = 0.0;

    for (double value : window.samplesMs)
    {
        const double difference = value - average;
        squaredDifferenceSum += difference * difference;
    }

    const double deviation =
        std::sqrt(
            squaredDifferenceSum /
            window.samplesMs.size()
        );

    const double elapsedSeconds =
        window.elapsedMs / 1000.0;

    const double samplesPerSecond =
        window.sampleCount / elapsedSeconds;

    const double theoreticalSamplesPerSecond =
        average > 0.0
        ? 1000.0 / average
        : 0.0;

    const double efficiencyPercent =
        theoreticalSamplesPerSecond > 0.0
        ? (samplesPerSecond / theoreticalSamplesPerSecond) * 100.0
        : 0.0;

    return {
        average,
        minimum,
        maximum,
        deviation,
        samplesPerSecond,
        theoreticalSamplesPerSecond,
        efficiencyPercent
    };
}