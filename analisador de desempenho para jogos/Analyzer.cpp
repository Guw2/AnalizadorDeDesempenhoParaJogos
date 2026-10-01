#include "Analyzer.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

namespace
{
    using clock_type =
        std::chrono::steady_clock;


    // isso aq força o processador a trabalhar e gerar latência entre as execuções
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

std::vector<double> collectSamples(
    std::size_t sampleCount
)
{
    std::vector<double> samples;

    samples.reserve(sampleCount);

    for (std::size_t i = 0; i < sampleCount; ++i)
    {
        const auto start =
            clock_type::now();

        runWorkload();

        const auto end =
            clock_type::now();

        // coletando duração sem o cast usado anteriormente
        const auto duration =
            std::chrono::duration<double, std::milli>(
                end - start
            );

        samples.push_back(
            duration.count()
        );
    }

    return samples;
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