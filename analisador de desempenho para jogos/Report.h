#pragma once

#include "Metrics.h"

#include <cstdint>
#include <filesystem>
#include <string>

std::string createReport(
    std::uint32_t session,
    const std::string& testName,
    const Metrics& metrics
);

void createReportsFolder(
    const std::filesystem::path& reports
);

void saveReport(
    const std::filesystem::path& reportFile,
    const std::string& report
);