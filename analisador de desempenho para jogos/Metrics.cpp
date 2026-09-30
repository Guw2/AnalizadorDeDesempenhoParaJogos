#include "Metrics.h"

#include <cmath>
#include <numeric>

Metrics calculateMetrics(std::vector<int>& fps) {
	if (fps.empty()) {
		return {};
	}

	const double avgFps = std::accumulate(std::begin(fps), std::end(fps), 0.0) / fps.size();

	double somaFrames = 0.0;

	for (int value : fps) {
		const double diff = value - avgFps;

		somaFrames += std::pow(diff, 2);
	}

	const double desAprox = std::sqrt(somaFrames / fps.size());

	return {
		avgFps, desAprox
	};
}