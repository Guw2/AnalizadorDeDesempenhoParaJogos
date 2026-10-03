#pragma once

#include "Models.h"

#include <filesystem>
#include <string>

void createReportsFolder(const std::filesystem::path& reportsFolder);

std::string buildTextReport(
    const SessionInfo& info,
    const AnalyzerConfig& config,
    const SessionResult& session
);

void saveTextReport(
    const std::filesystem::path& filePath,
    const std::string& report
);

void saveCsvReport(
    const std::filesystem::path& filePath,
    const SessionResult& session
);