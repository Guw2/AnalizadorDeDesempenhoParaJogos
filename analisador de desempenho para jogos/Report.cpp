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
    const std::string& game,
    const std::string& testMode,
    const Metrics& metrics,
    std::chrono::nanoseconds sortDuration
)
{
    std::ostringstream report;

    report
        << "Session: #"
        << session
        << "\n\n";

    report
        << "Game: "
        << game
        << "\n";

    report
        << "Modo Teste: "
        << testMode
        << "\n";

    report
        << std::fixed
        << std::setprecision(2);

    report
        << "Fps medio: "
        << metrics.avgFps
        << "\n";

    report
        << "Desvio aproximado: "
        << metrics.desApx
        << "\n";

    report
        << "Duracao de ordenacao: "
        << sortDuration.count()
        << "ns\n";

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