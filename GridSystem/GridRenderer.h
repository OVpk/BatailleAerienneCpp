#pragma once
#include "IGrid.h"
#include "IRenderableCell.h"
#include <iostream>

namespace GridSystem {

	class GridRenderer
	{
	private:
		inline void DrawCell(char content, std::string_view colorCode) const;
		inline void DrawHorizontalLine(int width) const;

	public:
		template<typename T>
		void DrawGrid(const IGrid<T>* grid) const;
	};

	// Fonction template pour pouvoir afficher une grille de nimporte quel type
	template<typename T>
	void GridRenderer::DrawGrid(const IGrid<T>* grid) const //const pour le parametre car l'affichage ne doit utiliser que les fonctions de IGrid qui ne modifient rien (const correctness)
	{
		if (!grid) return;

		int H = grid->getHeight();
		int W = grid->getWidth();

		std::cout << "  ";
		for (int j = 0; j < W; j++)
		{
			if (j < 10) std::cout << ' ' << j;
			else std::cout << j;
		}
		std::cout << '\n';

		std::cout << "  ";

		DrawHorizontalLine(W);
		for (int i = 0; i < H; i++)
		{
			if (i < 10) std::cout << ' ';
			std::cout << i << '|';

			for (int j = 0; j < W; j++)
			{
				const T* cellContent = grid->getCell(i, j);

				char symbol = ' ';
				std::string_view color = "\033[0m";

				if (cellContent) {
					const IRenderableCell* renderable = static_cast<const IRenderableCell*>(cellContent);
					symbol = renderable->getSymbol();
					color = renderable->getColor();
				}

				DrawCell(symbol, color);
				std::cout << '|';
			}
			std::cout << '\n';
			std::cout << "  ";
			DrawHorizontalLine(W);
		}
		std::cout << std::flush;
	}

	inline void GridRenderer::DrawCell(char content, std::string_view colorCode) const
	{
		std::cout << colorCode << content << "\033[0m";
	}

	inline void GridRenderer::DrawHorizontalLine(int width) const
	{
		for (int i = 0; i < width; i++) {
			std::cout << "+-";
		}
		std::cout << "+";
		std::cout << "\n";
	}

}