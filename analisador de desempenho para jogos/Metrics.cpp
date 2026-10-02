#include "Metrics.h"

#include <algorithm>
#include <cmath>
#include <numeric>

Metrics calculateMetrics(
    const std::vector<double>& samples,
    std::uint64_t sampleCount,
    double elapsedMs
)
{
    if (samples.empty() || elapsedMs <= 0.0)
    {
        return {};
    }

    const double soma =
        std::accumulate(
            samples.begin(),
            samples.end(),
            0.0
        );

    const double media =
        soma / samples.size();

    const double minimo =
        *std::min_element(
            samples.begin(),
            samples.end()
        );

    const double maximo =
        *std::max_element(
            samples.begin(),
            samples.end()
        );

    double somaDosQuadrados = 0.0;

    for (double valor : samples)
    {
        const double diferenca =
            valor - media;

        somaDosQuadrados +=
            diferenca * diferenca;
    }

    const double desvioAprox =
        std::sqrt(
            somaDosQuadrados / samples.size()
        );

    const double segundos =
        elapsedMs / 1000.0;

    const double samplesPerSecond =
        sampleCount / segundos;

    return {
        media,
        minimo,
        maximo,
        desvioAprox,
        samplesPerSecond
    };
}