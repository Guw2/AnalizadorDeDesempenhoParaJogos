#include <iostream>
#include <algorithm>

// máximo de fps no mock
#define MAX_MOCK_FPS_ARRAY 5

void showFps(const int fps[]) {
	for (int i = 0; i < MAX_MOCK_FPS_ARRAY; i++) {
		//mostra o fps medido
		std::cout << fps[i];

		// coloca uma vírgula caso tenha mais para mostrar
		if (i + 1 < MAX_MOCK_FPS_ARRAY) {
			std::cout << ", ";
		}
		else { // se não tiver mais ele quebra a linha
			std::cout << "\n";
		}
	}
}

int main() {

	// mock de medições de fps feitas pelo programa no jogo
	int fps[MAX_MOCK_FPS_ARRAY] = { 41, 62, 58, 77, 54 };

	std::cout << "FPS antes da ordenacao: ";
	showFps(fps);
	
	std::sort(fps, fps + 5);

	std::cout << "FPS depois da ordenacao: ";
	showFps(fps);

	return 0;
}