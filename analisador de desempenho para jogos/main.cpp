#include "Analyzer.h"
#include "Metrics.h"
#include "Report.h"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    const std::uint32_t session = 1504;

    const std::string testName =
        "CPU workload - janela de 1 segundo";

    const std::filesystem::path reports =
        "reports";

    createReportsFolder(reports);

    std::cout
        << "Iniciando coleta por 1 segundo...\n\n";

    std::vector<double> samples =
        collectSamples(
            std::chrono::milliseconds(1000)
        );

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