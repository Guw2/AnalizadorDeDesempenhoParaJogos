#include <iostream>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>

// máximo de fps no mock
#define MAX_MOCK_FPS_ARRAY 5

// mostra métricas
void showMetrics(const int fps[]) {
	// para não acontecer divisão por zero
	if (MAX_MOCK_FPS_ARRAY == 0) { return; }

	double fpsMedio = 0.0;
	double somaDosQuadrados = 0.0;

	for (int i = 0; i < MAX_MOCK_FPS_ARRAY; i++) {
		fpsMedio += fps[i];
	}

	fpsMedio /= MAX_MOCK_FPS_ARRAY;

	for (int i = 0; i < MAX_MOCK_FPS_ARRAY; i++) {
		double diferenca = fps[i] - fpsMedio;
		somaDosQuadrados += std::pow(diferenca, 2);
	}

	const double desvioAprox = std::sqrt(somaDosQuadrados / MAX_MOCK_FPS_ARRAY);

	std::cout << "Media de FPS: " << fpsMedio << std::endl;
	std::cout << "Desvio Aproximado: " << desvioAprox << std::endl;
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

	// mock de medições de fps feitas pelo programa no jogo
	int fps[MAX_MOCK_FPS_ARRAY] = { 47, 32, 61, 28, 55 };

	std::cout << "FPS antes da ordenacao: ";
	showFps(fps);

	// marca o início do sort
	auto inicio = std::chrono::high_resolution_clock::now();

	std::sort(fps, fps + 5);

	// marca o fim do sort
	auto fim = std::chrono::high_resolution_clock::now();

	std::cout << "FPS depois da ordenacao: ";
	showFps(fps);

	// calcula o tempo de sort
	auto duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);

	std::cout << std::endl;

	showMetrics(fps);
	std::cout << "Duracao de ordenacao: " << duracao.count() << "ns\n";

	return 0;
}