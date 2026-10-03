#include "Report.h"

#include <fstream>
#include <iomanip>
#include <sstream>

void createReportsFolder(const std::filesystem::path& reportsFolder)
{
    if (!std::filesystem::exists(reportsFolder))
    {
        std::filesystem::create_directories(reportsFolder);
    }
}

std::string buildTextReport(
    const SessionInfo& info,
    const AnalyzerConfig& config,
    const SessionResult& session
)
{
    std::ostringstream report;

    report << std::fixed << std::setprecision(3);

    report << "Session: #" << info.id << "\n";
    report << "Teste: " << info.testName << "\n";
    report << "Janelas: " << config.windowCount << "\n";
    report << "Duracao alvo por janela: "
        << config.windowDuration.count()
        << " ms\n\n";

    for (const WindowResult& result : session.windows)
    {
        report << "--- Janela " << result.id << " ---\n";
        report << "Duracao real: " << result.window.elapsedMs << " ms\n";
        report << "Amostras: " << result.window.sampleCount << "\n";
        report << "Tempo medio: " << result.metrics.avgMs << " ms\n";
        report << "Menor tempo: " << result.metrics.minMs << " ms\n";
        report << "Maior tempo: " << result.metrics.maxMs << " ms\n";
        report << "Desvio: " << result.metrics.desApx << " ms\n";
        report << "Taxa real: "
            << result.metrics.samplesPerSecond
            << " amostras/s\n";
        report << "Taxa teorica: "
            << result.metrics.theoreticalSamplesPerSecond
            << " amostras/s\n";
        report << "Eficiencia: "
            << result.metrics.efficiencyPercent
            << "%\n\n";
    }

    report << "=== Resumo da sessao ===\n";
    report << "Total de amostras: " << session.summary.totalSamples << "\n";
    report << "Tempo total observado: " << session.summary.totalElapsedMs << " ms\n";
    report << "Tempo medio global: " << session.summary.overallAvgMs << " ms\n";
    report << "Melhor janela: #" << session.summary.bestWindowId << "\n";
    report << "Pior janela: #" << session.summary.worstWindowId << "\n";

    return report.str();
}

void saveTextReport(
    const std::filesystem::path& filePath,
    const std::string& report
)
{
    std::ofstream file(filePath);

    if (file.is_open())
    {
        file << report;
    }
}

void saveCsvReport(
    const std::filesystem::path& filePath,
    const SessionResult& session
)
{
    std::ofstream file(filePath);

    if (!file.is_open())
    {
        return;
    }

    file << "window_id,elapsed_ms,sample_count,avg_ms,min_ms,max_ms,deviation_ms,"
        "samples_per_second,theoretical_samples_per_second,efficiency_percent\n";

    file << std::fixed << std::setprecision(6);

    for (const WindowResult& result : session.windows)
    {
        file
            << result.id << ','
            << result.window.elapsedMs << ','
            << result.window.sampleCount << ','
            << result.metrics.avgMs << ','
            << result.metrics.minMs << ','
            << result.metrics.maxMs << ','
            << result.metrics.desApx << ','
            << result.metrics.samplesPerSecond << ','
            << result.metrics.theoreticalSamplesPerSecond << ','
            << result.metrics.efficiencyPercent
            << '\n';
    }
}