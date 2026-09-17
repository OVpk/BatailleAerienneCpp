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
	void DrawGrid(Grid* grid);
};

