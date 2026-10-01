#pragma once

#include <vector>

struct Metrics
{
    double avgMs = 0.0;
    double minMs = 0.0;
    double maxMs = 0.0;
    double desApx = 0.0;
};

Metrics calculateMetrics(
    const std::vector<double>& samples
);