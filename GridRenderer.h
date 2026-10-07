#pragma once
#include "IGrid.h"
#include "IRenderableCell.h"
#include <iostream>
#include <string_view>

class GridRenderer
{
private:
	inline void DrawCell(char content, std::string_view colorCode);
	inline void DrawHorizontalLine(int width);

public:
	template<typename T>
	void DrawGrid(const IGrid<T>* grid);
};

// Fonction template pour pouvoir afficher une grille de nimporte quel type
template<typename T>
void GridRenderer::DrawGrid(const IGrid<T>* grid) //const car l'affichage ne doit utiliser que les fonctions qui ne modifient rien (const correctness)
{
	if (!grid) return;

	int H = grid->getHeight();
	int W = grid->getWidth();

	DrawHorizontalLine(W);
	for (int i = 0; i < H; i++)
	{
		std::cout << '|';
		for (int j = 0; j < W; j++)
		{
			T* cellContent = grid->getCell(i, j);

			char symbol = ' ';
			std::string_view color = "\033[0m";

			if (cellContent) {
				IRenderableCell* renderable = static_cast<IRenderableCell*>(cellContent);
				symbol = renderable->getSymbol();
				color = renderable->getColor();
			}

			DrawCell(symbol, color);
			std::cout << '|';
		}
		std::cout << '/n';
		DrawHorizontalLine(W);
	}
	std::cout << std::flush;
}

inline void GridRenderer::DrawCell(char content, std::string_view colorCode)
{
	std::cout << colorCode << content << "\033[0m";
}

inline void GridRenderer::DrawHorizontalLine(int width)
{
	for (int i = 0; i < width; i++) {
		std::cout << "+-";
	}
	std::cout << "+";
	std::cout << std::endl;
}