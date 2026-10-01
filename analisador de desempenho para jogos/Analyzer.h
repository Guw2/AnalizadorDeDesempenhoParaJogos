#pragma once

#include <cstddef>
#include <vector>

std::vector<double> collectSamples(
    std::size_t sampleCount
);

void showSamples(
    const std::vector<double>& samples
);