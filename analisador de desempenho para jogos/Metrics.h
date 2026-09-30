#pragma once

#include <vector>

// strcut para agrupar valores relacionados a métrica
struct Metrics {
	double avgFps = 0.0;
	double desApx = 0.0;
};

Metrics calculateMetrics(std::vector<int>& fps);