#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			tab[i][j] = nullptr;
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (tab[i][j] != nullptr)
			{
				delete tab[i][j];
			}
		}
	}
}

Cell* Grid::getCellule(int row, int collumn)
{
	if (!IsCellValide(row, collumn)) {
		return nullptr;
	}

	return tab[row][collumn];
}

bool Grid::setCellule(int row, int collumn, Cell* nouvelleCellule)
{
	if (IsCellValide(row, collumn)) 
	{
		if (tab[row][collumn] != nullptr) {
			delete tab[row][collumn];
		}
		tab[row][collumn] = nouvelleCellule;
		return true;
	}
	return false;
}

bool Grid::IsCellValide(int row, int collumn)
{
	bool isRowValide = row >= 0 && row < HEIGHT;
	bool isCollumnValide = collumn >= 0 && collumn < WIDTH;
	return isRowValide && isCollumnValide;
}