#include "Analyzer.h"
#include "Metrics.h"
#include "Report.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    const std::uint32_t session = 1503;

    const std::string testName =
        "CPU workload";

    const std::filesystem::path reports =
        "reports";

    createReportsFolder(reports);

    std::cout
        << "Iniciando coleta...\n\n";

    std::vector<double> samples =
        collectSamples(20);

    showSamples(samples);

    const Metrics metrics =
        calculateMetrics(samples);

    const std::string report =
        createReport(
            session,
            testName,
            metrics
        );

    const std::filesystem::path reportFile =
        reports / "report.txt";

    std::cout
        << "\n--- REPORT ---\n"
        << report
        << "\n";

    saveReport(
        reportFile,
        report
    );

    return 0;
}