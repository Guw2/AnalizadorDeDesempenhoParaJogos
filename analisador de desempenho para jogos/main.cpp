#include <iostream>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <numeric>

// máximo de fps no mock
#define MAX_MOCK_FPS_ARRAY 5

struct Metrics {
	double avgFps;
	double desApx;
};

// mostra métricas
std::vector<double> showMetrics(const int fps[]) {
	// para não acontecer divisão por zero
	if (MAX_MOCK_FPS_ARRAY == 0) { return {}; }

	const double fpsMedio = std::accumulate(fps, fps+MAX_MOCK_FPS_ARRAY, 0.0) / MAX_MOCK_FPS_ARRAY;
	double somaDosQuadrados = 0.0;

	for (int i = 0; i < MAX_MOCK_FPS_ARRAY; i++) {
		double diferenca = fps[i] - fpsMedio;
		somaDosQuadrados += std::pow(diferenca, 2);
	}

	const double desvioAprox = std::sqrt(somaDosQuadrados / MAX_MOCK_FPS_ARRAY);

	const std::vector<double> finalMetrics = {fpsMedio, desvioAprox};

	return finalMetrics;
}

void showFps(const int fps[]) {
	
	std::atomic<int> count = 0;

	for (int i = 0; i < MAX_MOCK_FPS_ARRAY; i++) {
		//mostra o fps medido
		std::cout << fps[i]; count++;

		// coloca uma vírgula caso tenha mais para mostrar
		if (i + 1 < MAX_MOCK_FPS_ARRAY) {
			std::cout << ", ";
		}
		else { // se não tiver mais ele quebra a linha
			std::cout << "\n";
		}
	}

	std::cout << "Medidas processadas: " << count << std::endl;
}

int main() {

	uint32_t session = 1502;
	std::cout << "Session: #" << session << "\n\n";

	std::filesystem::path reports = "reports";

	if (!std::filesystem::exists(reports)) {
		std::filesystem::create_directory(reports);

		std::cout << "Pasta de reports criada" << std::endl;
	}

	// mock de medições de fps feitas pelo programa no jogo
	int fps[MAX_MOCK_FPS_ARRAY] = { 47, 32, 61, 28, 55 };

	std::cout << "FPS antes da ordenacao: ";
	showFps(fps);

	// marca o início do sort
	auto inicio = std::chrono::high_resolution_clock::now();

	std::sort(std::begin(fps), std::end(fps));

	// marca o fim do sort
	auto fim = std::chrono::high_resolution_clock::now();

	std::cout << "FPS depois da ordenacao: ";
	showFps(fps);

	// calcula o tempo de sort
	auto duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

	std::cout << std::endl;

	std::vector<double> metricsList = showMetrics(fps);
	Metrics metrics;

	metrics.avgFps = metricsList[0];
	metrics.desApx = metricsList[1];

	std::cout << std::fixed << std::setprecision(2);

	std::cout << "Fps medio: " << metrics.avgFps << std::endl;
	std::cout << "Desvio aproximado: " << metrics.desApx << std::endl;

	std::cout << "Duracao de ordenacao: " << duracao.count() << "ns\n";

	std::filesystem::path reportFile = reports / "report.txt";

	std::ofstream file(reportFile);

	if (file.is_open()) {
		file << "Session #" << session << "\n\n";
		file << "Avg Fps: " << metrics.avgFps << "\n";
		file << "Apx Dev: " << metrics.desApx << "\n";

		file.close();
	}

	return 0;
}