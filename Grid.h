#pragma once

//Template declaration
template <typename T, int H, int W>
class Grid {
private:
	static constexpr int HEIGHT = H;
	static constexpr int WIDTH = W;

	T* tab[HEIGHT][WIDTH];

	bool IsCellValide(int row, int collumn);

public:
	Grid();
	~Grid();

	T* getCell(int row, int collumn);
	bool setCell(int row, int collumn, T* newCell);

	static constexpr int getHeight() { return HEIGHT; }
	static constexpr int getWidth() { return WIDTH; }
};

//template implementation
template <typename T, int H, int W>
inline Grid<T, H, W>::Grid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			tab[i][j] = nullptr;
		}
	}
}

template <typename T, int H, int W>
inline Grid<T, H, W>::~Grid()
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

template <typename T, int H, int W>
inline T* Grid<T, H, W>::getCell(int row, int collumn)
{
	if (!IsCellValide(row, collumn)) {
		return nullptr;
	}

	return tab[row][collumn];
}

template <typename T, int H, int W>
inline bool Grid<T, H, W>::setCell(int row, int collumn, T* newCell)
{
	if (IsCellValide(row, collumn))
	{
		if (tab[row][collumn] != nullptr) {
			delete tab[row][collumn];
		}
		tab[row][collumn] = newCell;
		return true;
	}
	return false;
}

template <typename T, int H, int W>
inline bool Grid<T, H, W>::IsCellValide(int row, int collumn)
{
	bool isRowValide = row >= 0 && row < HEIGHT;
	bool isCollumnValide = collumn >= 0 && collumn < WIDTH;
	return isRowValide && isCollumnValide;
}
