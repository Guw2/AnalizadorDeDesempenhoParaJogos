#include "Models.h"
#include "Report.h"
#include "Session.h"

#include <cstdint>
#include <filesystem>
#include <iostream>

int main()
{
    const SessionInfo sessionInfo{
        1506,
        "CPU workload - multi window"
    };

    const AnalyzerConfig config{
        std::chrono::milliseconds(1000),
        3,
        1000
    };

    const std::filesystem::path reportsFolder = "reports";

    createReportsFolder(reportsFolder);

    std::cout << "Iniciando sessao #" << sessionInfo.id << "...\n";
    std::cout << "Janelas: " << config.windowCount << "\n";
    std::cout << "Duracao por janela: "
        << config.windowDuration.count()
        << " ms\n\n";

    const SessionResult session = runSession(config);

    const std::string textReport =
        buildTextReport(
            sessionInfo,
            config,
            session
        );

    std::cout << textReport << '\n';

    saveTextReport(
        reportsFolder / "report.txt",
        textReport
    );

    saveCsvReport(
        reportsFolder / "windows.csv",
        session
    );

    std::cout << "Reports salvos em: "
        << std::filesystem::absolute(reportsFolder)
        << '\n';

    return 0;
}