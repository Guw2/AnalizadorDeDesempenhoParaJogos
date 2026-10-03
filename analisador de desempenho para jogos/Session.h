#pragma once

#include "Models.h"

SessionResult runSession(const AnalyzerConfig& config);
SessionSummary summarizeSession(const std::vector<WindowResult>& windows);