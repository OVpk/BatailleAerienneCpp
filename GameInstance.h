#pragma once
#include "IGrid.h"
#include "GridRenderer.h"
#include "Player.h"
#include "Target.h"

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