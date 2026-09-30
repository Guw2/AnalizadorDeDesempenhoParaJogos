#include <iostream>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

// máximo de fps no mock
#define MAX_MOCK_FPS_ARRAY 5

struct Metrics {
	double avgFps;
	double desApx;
};

// mostra métricas
Metrics showMetrics(const std::vector<int>& fps) {

	// para não acontecer divisão por zero
	if (fps.empty()) {
		return {};
	}

	const double fpsMedio =
		std::accumulate(
			std::begin(fps),
			std::end(fps),
			0.0
		) / fps.size();

	double somaDosQuadrados = 0.0;

	for (int valor : fps) {
		double diferenca = valor - fpsMedio;

		somaDosQuadrados += std::pow(diferenca, 2);
	}

	const double desvioAprox =
		std::sqrt(somaDosQuadrados / fps.size());

	return {
		fpsMedio,
		desvioAprox
	};
}

void showFps(const std::vector<int>& fps) {

	std::atomic<int> count = 0;

	for (std::size_t i = 0; i < fps.size(); i++) {

		//mostra o fps medido
		std::cout << fps[i];
		count++;

		// coloca uma vírgula caso tenha mais para mostrar
		if (i + 1 < fps.size()) {
			std::cout << ", ";
		}
		else { // se não tiver mais ele quebra a linha
			std::cout << "\n";
		}
	}

	std::cout
		<< "Medidas processadas: "
		<< count
		<< std::endl;
}

void createReportsFolder(const std::filesystem::path& reports) {

	if (!std::filesystem::exists(reports)) {
		std::filesystem::create_directory(reports);

		std::cout
			<< "Pasta de reports criada"
			<< std::endl;
	}
}

std::string createReport(
	uint32_t session,
	const std::string& game,
	const std::string& testMode,
	const Metrics& metrics,
	std::chrono::nanoseconds duracao
) {

	std::ostringstream report;

	report << "Session: #" << session << "\n\n";

	report << "Game: " << game << std::endl;
	report << "Modo Teste: " << testMode << std::endl;

	report << std::fixed << std::setprecision(2);

	report << "Fps medio: " << metrics.avgFps << std::endl;
	report << "Desvio aproximado: " << metrics.desApx << std::endl;

	report
		<< "Duracao de ordenacao: "
		<< duracao.count()
		<< "ns\n";

	return report.str();
}

void saveReport(
	const std::filesystem::path& reportFile,
	const std::string& reportString
) {

	std::ofstream file(reportFile);

	if (file.is_open()) {
		file << reportString;

		file.close();
	}
}

int main() {

	uint32_t session = 1502;

	std::string game = "The Witness";
	std::string testMode = "720p s/ Vsync";

	std::filesystem::path reports = "reports";

	createReportsFolder(reports);

	// mock de medições de fps feitas pelo programa no jogo
	std::vector<int> fps = {
		47,
		32,
		61,
		28,
		55
	};

	std::cout << "FPS antes da ordenacao: ";
	showFps(fps);

	// marca o início do sort
	auto inicio =
		std::chrono::high_resolution_clock::now();

	std::sort(
		std::begin(fps),
		std::end(fps)
	);

	// marca o fim do sort
	auto fim =
		std::chrono::high_resolution_clock::now();

	std::cout << "FPS depois da ordenacao: ";
	showFps(fps);

	// calcula o tempo de sort
	auto duracao =
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			fim - inicio
		);

	std::cout << std::endl;

	Metrics metrics = showMetrics(fps);

	std::string reportString = createReport(
		session,
		game,
		testMode,
		metrics,
		duracao
	);

	std::filesystem::path reportFile =
		reports / "report.txt";

	std::cout << reportString << std::endl;

	saveReport(
		reportFile,
		reportString
	);

	return 0;
}