#include "Metrics.h"

#include <algorithm>
#include <cmath>
#include <numeric>

Metrics calculateMetrics(
    const std::vector<double>& samples
)
{
    if (samples.empty())
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

    return {
        media,
        minimo,
        maximo,
        desvioAprox
    };
}