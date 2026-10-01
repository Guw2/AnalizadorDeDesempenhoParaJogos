#pragma once

#include <chrono>
#include <vector>

std::vector<double> collectSamples(
    std::chrono::milliseconds windowDuration
);

void showSamples(
    const std::vector<double>& samples
);