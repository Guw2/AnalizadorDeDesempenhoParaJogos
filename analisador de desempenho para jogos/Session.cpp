#include "Session.h"

#include "Analyzer.h"
#include "Metrics.h"

#include <limits>

SessionResult runSession(const AnalyzerConfig& config)
{
    SessionResult session;
    session.windows.reserve(config.windowCount);

    for (std::uint32_t i = 0; i < config.windowCount; ++i)
    {
        SampleWindow window = collectWindow(config);
        Metrics metrics = calculateMetrics(window);

        WindowResult result;
        result.id = i + 1;
        result.window = std::move(window);
        result.metrics = metrics;

        session.windows.push_back(std::move(result));
    }

    session.summary = summarizeSession(session.windows);

    return session;
}

SessionSummary summarizeSession(const std::vector<WindowResult>& windows)
{
    SessionSummary summary;

    if (windows.empty())
    {
        return summary;
    }

    double totalSampleTimeMs = 0.0;
    double bestAverage = std::numeric_limits<double>::max();
    double worstAverage = std::numeric_limits<double>::lowest();

    for (const WindowResult& result : windows)
    {
        summary.totalSamples += result.window.sampleCount;
        summary.totalElapsedMs += result.window.elapsedMs;

        for (double sample : result.window.samplesMs)
        {
            totalSampleTimeMs += sample;
        }

        if (result.metrics.avgMs < bestAverage)
        {
            bestAverage = result.metrics.avgMs;
            summary.bestWindowId = result.id;
        }

        if (result.metrics.avgMs > worstAverage)
        {
            worstAverage = result.metrics.avgMs;
            summary.worstWindowId = result.id;
        }
    }

    if (summary.totalSamples > 0)
    {
        summary.overallAvgMs =
            totalSampleTimeMs /
            summary.totalSamples;
    }

    return summary;
}