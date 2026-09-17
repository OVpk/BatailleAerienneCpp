#pragma once
#include "Cell.h"

class Grid {
private:
	static constexpr int HEIGHT =10;
	static constexpr int WIDTH =10;
	Cell* tab[HEIGHT][WIDTH];

	bool IsCellValide(int row, int collumn);

public:
	Grid();
	~Grid();

	Cell* getCellule(int row, int collumn);
	bool setCellule(int row, int collumn, Cell* nouvelleCellule);

	static constexpr int getHeight() { return HEIGHT; }
	static constexpr int getWidth() { return WIDTH; }
};

