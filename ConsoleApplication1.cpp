#include <iostream>
#include <random>

int main() {
	constexpr int min = 0, max = 10;

    int random_nb = min + std::rand() % (max - min);

    int input = 0;

    do {
        std::cout << "Donnez un nombre entre" << min << "et" << max << std::endl;
        std::cin >> input;
    } while (input != random_nb);

    std::cout << "Gagné !" << std::endl;

	return 0;
}