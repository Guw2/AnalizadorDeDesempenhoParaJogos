#include "Analyzer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

namespace
{
    using clock_type =
        std::chrono::steady_clock;

    void runWorkload()
    {
        std::vector<int> numbers = {
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

        for (int i = 0; i < 1000; ++i)
        {
            std::sort(
                numbers.begin(),
                numbers.end()
            );

            std::reverse(
                numbers.begin(),
                numbers.end()
            );
        }
    }
}

SampleWindow collectSamples(
    std::chrono::milliseconds windowDuration
)
{
    SampleWindow window;

    const auto windowStart =
        clock_type::now();

    while (
        clock_type::now() - windowStart
        < windowDuration
        )
    {
        const auto sampleStart =
            clock_type::now();

        runWorkload();

        const auto sampleEnd =
            clock_type::now();

        const auto duration =
            std::chrono::duration<double, std::milli>(
                sampleEnd - sampleStart
            );

        window.samples.push_back(
            duration.count()
        );

        window.sampleCount++;
    }

    const auto windowEnd =
        clock_type::now();

    const auto elapsed =
        std::chrono::duration<double, std::milli>(
            windowEnd - windowStart
        );

    window.elapsedMs =
        elapsed.count();

    return window;
}

void showSamples(
    const std::vector<double>& samples
)
{
    for (std::size_t i = 0; i < samples.size(); ++i)
    {
        std::cout
            << "Amostra "
            << i + 1
            << ": "
            << samples[i]
            << " ms\n";
    }
}