#include "Report.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

void createReportsFolder(
    const std::filesystem::path& reports
)
{
    if (!std::filesystem::exists(reports))
    {
        std::filesystem::create_directory(reports);

        std::cout
            << "Pasta de reports criada\n";
    }
}

std::string createReport(
    std::uint32_t session,
    const std::string& testName,
    const Metrics& metrics
)
{
    std::ostringstream report;

    report
        << std::fixed
        << std::setprecision(3);

    report
        << "Session: #"
        << session
        << "\n\n";

    report
        << "Teste: "
        << testName
        << "\n\n";

    report
        << "Tempo medio: "
        << metrics.avgMs
        << " ms\n";

    report
        << "Menor tempo: "
        << metrics.minMs
        << " ms\n";

    report
        << "Maior tempo: "
        << metrics.maxMs
        << " ms\n";

    report
        << "Desvio aproximado: "
        << metrics.desApx
        << " ms\n";

    return report.str();
}

void saveReport(
    const std::filesystem::path& reportFile,
    const std::string& report
)
{
    std::ofstream file(reportFile);

    if (file.is_open())
    {
        file << report;
    }
}