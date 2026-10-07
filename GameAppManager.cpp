#include "GameAppManager.h"

GameAppManager::GameAppManager()
{
}

GameAppManager::~GameAppManager()
{
}

int GameAppManager::Run()
{
	isRun = true;
	while (isRun)
	{
		MainMenu();
	}
	return 0;
}

void GameAppManager::MainMenu()
{
	std::cout << "Menu Principal\n";
	std::cout << "Choisissez une difficultee pour lancer une partie (tapez 1, 2 ou 3)\n";
	std::cout << "Pour quitter, tapez 4\n";
	std::cout << "Votre choix :\n";

	std::string input;
	std::getline(std::cin, input);
	char choice = input.empty() ? '0' : input[0];

	std::system("cls");

	switch (choice)
	{
	case '1':
		StartNewGame(Difficulty::Easy);
		break;
	case '2':
		StartNewGame(Difficulty::Normal);
		break;
	case '3':
		StartNewGame(Difficulty::Hard);
		break;
	case '4':
		isRun = false;
		break;
	default:
		std::cout << "Choix Invalide\n";
		std::cout << "Appuyez sur Entree pour reessayer...\n";

		std::getline(std::cin, input);
		std::system("cls");
		break;
	}
}

void GameAppManager::StartNewGame(Difficulty difficulty)
{
	GridSystem::IGrid<Target>* selectedGrid = nullptr;
	switch (difficulty)
	{
	case Difficulty::Easy:
		grilleFacile.clear();
		selectedGrid = &grilleFacile;
		break;
	case Difficulty::Normal:
		grilleNormale.clear();
		selectedGrid = &grilleNormale;
		break;
	case Difficulty::Hard:
		grilleDifficile.clear();
		selectedGrid = &grilleDifficile;
		break;
	default:
		break;
	}

	currentMatch = new GameInstance(selectedGrid, renderer, P1, P2);
	currentMatch->StartGameLoop(); //Le programme va rester bloqué là tant que la partie joue sa propre boucle

	//puis quand la partie est fini, il va la détruire pour retourner sur le menu principal
	delete currentMatch;
	currentMatch = nullptr;
}
