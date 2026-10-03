#include "Analyzer.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>

namespace
{
    using clock_type = std::chrono::steady_clock;

    volatile std::uint64_t g_workloadSink = 0;

    void runWorkload(std::uint32_t iterations)
    {
        std::array<int, 10> numbers = {
            923,
            15,
            742,
            81,
            400,
            37,
            651,
            202,
            99,
            518
        };

        for (std::uint32_t i = 0; i < iterations; ++i)
        {
            std::sort(numbers.begin(), numbers.end());
            std::reverse(numbers.begin(), numbers.end());

            // Impede o compilador de considerar o workload completamente descartavel.
            g_workloadSink ^= numbers.front();
        }
    }
}

SampleWindow collectWindow(const AnalyzerConfig& config)
{
    SampleWindow result;

    const auto windowStart = clock_type::now();

    while (clock_type::now() - windowStart < config.windowDuration)
    {
        const auto sampleStart = clock_type::now();

        runWorkload(config.workloadIterations);

        const auto sampleEnd = clock_type::now();

        const auto sampleDuration =
            std::chrono::duration<double, std::milli>(
                sampleEnd - sampleStart
            );

        result.samplesMs.push_back(sampleDuration.count());
        result.sampleCount++;
    }

    const auto windowEnd = clock_type::now();

    result.elapsedMs =
        std::chrono::duration<double, std::milli>(
            windowEnd - windowStart
        ).count();

    return result;
}