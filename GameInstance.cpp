#include "GameInstance.h"
#include "Plane.h"
#include "Drone.h"

#include <cstdlib>
#include <ctime>
#include <string>


void GameInstance::InitBoard()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //pour initialiser random (trouvé sur internet mais ça me semble sale)

	SpawnTargetsRandom<Target>(TARGETS_PER_PLAYER, &p1);
	SpawnTargetsRandom<Drone>(DRONES_PER_PLAYER, &p1);
	SpawnTargetsRandom<Plane>(PLANES_PER_PLAYER, &p1);

	SpawnTargetsRandom<Target>(TARGETS_PER_PLAYER, &p2);
	SpawnTargetsRandom<Drone>(DRONES_PER_PLAYER, &p2);
	SpawnTargetsRandom<Plane>(PLANES_PER_PLAYER, &p2);
}

void GameInstance::StartGameLoop()
{
	InitBoard();

	bool isGamePlaying = true;

	Player* currentPlayer = &p1;

	while (isGamePlaying)
	{
		std::cout << "\n Joueur Actuel : " << currentPlayer->color << currentPlayer->playerName << "\033[0m ---\n";
		renderer.DrawGrid(currentGrid);


		std::cout << "\nEntrez les coordonnees d'une cellule : \n";
		std::string input;
		std::getline(std::cin, input);

		if (!input.empty() && (input[0] == 'q' || input[0] == 'Q'))
		{
			isGamePlaying = false;
			continue;
		}

		currentPlayer = (currentPlayer == &p1) ? &p2 : &p1;
	}

	std::cout << "Retour au menu principal...\n";
}
