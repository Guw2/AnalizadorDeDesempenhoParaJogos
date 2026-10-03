#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

struct AnalyzerConfig
{
    std::chrono::milliseconds windowDuration{ 1000 };
    std::uint32_t windowCount = 3;
    std::uint32_t workloadIterations = 1000;
};

struct SessionInfo
{
    std::uint32_t id = 0;
    std::string testName;
};

struct SampleWindow
{
    std::vector<double> samplesMs;
    std::uint64_t sampleCount = 0;
    double elapsedMs = 0.0;
};

struct Metrics
{
    double avgMs = 0.0;
    double minMs = 0.0;
    double maxMs = 0.0;
    double desApx = 0.0;

    double samplesPerSecond = 0.0;
    double theoreticalSamplesPerSecond = 0.0;
    double efficiencyPercent = 0.0;
};

struct WindowResult
{
    std::uint64_t id = 0;
    SampleWindow window;
    Metrics metrics;
};

struct SessionSummary
{
    std::uint64_t totalSamples = 0;
    double totalElapsedMs = 0.0;
    double overallAvgMs = 0.0;

    std::uint64_t bestWindowId = 0;
    std::uint64_t worstWindowId = 0;
};

struct SessionResult
{
    std::vector<WindowResult> windows;
    SessionSummary summary;
};