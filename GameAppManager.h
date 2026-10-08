#pragma once
#include "Grid.h"
#include "GridRenderer.h"
#include "Player.h"
#include "Target.h"
#include "GameInstance.h"
#include <string>

inline constexpr std::string_view ROUGE = "\033[31m";
inline constexpr std::string_view BLEU = "\033[34m";

enum class Difficulty
{
	Easy,
	Normal,
	Hard
};

class GameAppManager
{
private:
	GameAppManager(); //pas de copies + constructeur en privé = singleton
	GameAppManager(const GameAppManager&) = delete;
	GameAppManager& operator=(const GameAppManager&) = delete;
	~GameAppManager();

	GridSystem::GridRenderer renderer;
	Player P1 = Player("J1", BLEU);
	Player P2 = Player("J2", ROUGE);

	GridSystem::Grid<Target, 10, 10> grilleFacile;
	GridSystem::Grid<Target, 15, 15> grilleNormale;
	GridSystem::Grid<Target, 20, 20> grilleDifficile;

	GameInstance* currentMatch = nullptr;

	bool isRun = false;

	void MainMenu();
	

public:
	static GameAppManager& GetInstance()
	{
		static GameAppManager instance;
		return instance;
	}

	int Run();

	void StartNewGame(Difficulty difficulty);
};

