#pragma once
#include "IGrid.h"
#include "GridRenderer.h"
#include "Player.h"
#include "Target.h"
#include "Unit.h"

//#define DEV_MODE

class GameInstance
{
private:
	static constexpr int TARGETS_PER_PLAYER = 4;
	static constexpr int DRONES_PER_PLAYER = 3;
	static constexpr int PLANES_PER_PLAYER = 5;

	GridSystem::IGrid<Target>* currentGrid;
	const GridSystem::GridRenderer& renderer;
	Player& p1;
	Player& p2;

	void InitBoard();
	bool SelectActionMenu(Target* target, Player* currentPlayer, int row, int collumn);
	void Analyse(Target* target, bool isOwner) const;
	bool Move(Unit* unit, int startRow, int startCollumn);
	bool Attack(Unit* unit, int startRow, int startCollumn);

	template<typename T>
	void SpawnTargetsRandom(int count, Player* owner);

public:
	GameInstance(GridSystem::IGrid<Target>* grid, GridSystem::GridRenderer& rendererRef, Player& player1, Player& player2)
		: currentGrid(grid), renderer(rendererRef), p1(player1), p2(player2){ }

	void StartGameLoop();
};

template<typename T>
void GameInstance::SpawnTargetsRandom(int count, Player* owner)
{
	for (int i = 0; i < count; ++i)
	{
		int row, collumn;
		do{
			row = rand() % currentGrid->getHeight();
			collumn = rand() % currentGrid->getWidth();
		}while (!currentGrid->isEmpty(row, collumn));

		Target* newTarget = new T(owner);
		currentGrid->setCell(row, collumn, newTarget);
	}
}