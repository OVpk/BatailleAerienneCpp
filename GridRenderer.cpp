#include "GridRenderer.h"

void GridRenderer::DrawGrid(Grid* grid)
{
	if (!grid) return;

	DrawHorizontalLine(Grid::getWidth());
	for (int i = 0; i < Grid::getHeight(); i++)
	{
		std::cout << "|";
		for (int j = 0; j < Grid::getWidth(); j++)
		{
			DrawCell();
			std::cout << "|";
		}
		std::cout << std::endl;
		DrawHorizontalLine(Grid::getWidth());
	}
}

void GridRenderer::DrawCell(char content)
{
	std::cout << content;
}

void GridRenderer::DrawHorizontalLine(int width)
{
	for (int i = 0; i < width; i++) {
		std::cout << "+-";
	}
	std::cout << "+";
	std::cout << std::endl;
}
