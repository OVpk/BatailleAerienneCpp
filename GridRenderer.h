#pragma once
#include "Cell.h"
#include "Grid.h"

#include <iostream>

class GridRenderer
{
private:
	void DrawCell(char content = ' ');
	void DrawHorizontalLine(int width);

public:
	template<typename T, int H, int W>
	void DrawGrid(Grid<T,H,W>* grid);
};

template<typename T, int H, int W>
void GridRenderer::DrawGrid(Grid<T, H, W>* grid)
{
	if (!grid) return;

	DrawHorizontalLine(W);
	for (int i = 0; i < H; i++)
	{
		std::cout << "|";
		for (int j = 0; j < W; j++)
		{
			T* cellule = grid->getCellule(i, j);
			char symbol = ' ';

			if (cellule != nullptr)
			{
				symbol = cellule->getSymbol();
			}

			DrawCell(symbol);
			std::cout << "|";
		}
		std::cout << std::endl;
		DrawHorizontalLine(W);
	}
}
