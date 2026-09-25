#include "GridRenderer.h"

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
