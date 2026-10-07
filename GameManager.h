#pragma once
#include "Grid.h"
#include "GridRenderer.h"
#include "Player.h"

#define ROUGE   "\033[31m"
#define BLEU    "\033[34m"

class GameManager
{
public:
	Grid<Cell, 10, 10> grilleFacile;
	Grid<Cell, 15, 15> grilleNormale;
	Grid<Cell, 20, 20> grilleDifficile;
	GridRenderer* renderer = new GridRenderer();

	Player* P1 = new Player(BLEU);
	Player* P2 = new Player(ROUGE);

	void InitGame();

private:
	void DispatchProps(int propsPerPlayer);
};

