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
    std::uint32_t session = 1502;

    std::string game =
        "The Witness";

    std::string testMode =
        "720p s/ Vsync";

    std::filesystem::path reports =
        "reports";

    createReportsFolder(reports);

    // mock de medições de fps feitas pelo programa no jogo
    std::vector<int> fps = {
        47,
        32,
        61,
        28,
        55
    };

    std::cout
        << "FPS antes da ordenacao: ";

    showFps(fps);

    // início do sort
    auto inicio =
        std::chrono::steady_clock::now();

    sortFps(fps);

    // fim do sort
    auto fim =
        std::chrono::steady_clock::now();

    std::cout
        << "FPS depois da ordenacao: ";

    showFps(fps);

    // calcula tempo de sort
    auto duracao =
        std::chrono::duration_cast<
        std::chrono::nanoseconds
        >(
            fim - inicio
        );

    Metrics metrics =
        calculateMetrics(fps);

    std::string report =
        createReport(
            session,
            game,
            testMode,
            metrics,
            duracao
        );

    std::filesystem::path reportFile =
        reports / "report.txt";

    std::cout
        << "\n"
        << report
        << "\n";

    saveReport(
        reportFile,
        report
    );

    return 0;
}