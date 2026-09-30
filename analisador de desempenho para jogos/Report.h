#pragma once

#include "Metrics.h"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>

std::string createReport(
    std::uint32_t session,
    const std::string& game,
    const std::string& testMode,
    const Metrics& metrics,
    std::chrono::nanoseconds sortDuration
);

void createReportsFolder(
    const std::filesystem::path& reports
);

void saveReport(
    const std::filesystem::path& reportFile,
    const std::string& report
);