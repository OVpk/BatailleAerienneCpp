#pragma once
#include "IGrid.h"

namespace GridSystem {

	//Template declaration
	template <typename T, int H, int W>
	class Grid : public IGrid<T> {
	private:
		static constexpr int HEIGHT = H;
		static constexpr int WIDTH = W;

		T* tab[HEIGHT][WIDTH];

		bool IsCellValide(int row, int collumn) const;

	public:
		Grid();
		Grid(const Grid&) = delete; //le reste du programme n'est pas sensé manipuler les grilles directement, il doit passer par IGrid. Je bloque la copie pour éviter un double free sur les objets dans les cellules
		Grid& operator=(const Grid&) = delete;

		~Grid() override;

		T* getCell(int row, int collumn) const override;
		bool setCell(int row, int collumn, T* newCell) override;
		bool moveCell(int oldRow, int oldCollumn, int newRow, int newCollumn) override;
		bool removeCell(int row, int column) override;
		bool isEmpty(int row, int column) const override;
		void clear() override;

		int getHeight() const override { return HEIGHT; }
		int getWidth() const override { return WIDTH; }
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
	inline T* Grid<T, H, W>::getCell(int row, int collumn) const
	{
		if (!IsCellValide(row, collumn))
		{
			return nullptr;
		}

		return tab[row][collumn];
	}

	template <typename T, int H, int W>
	inline bool Grid<T, H, W>::setCell(int row, int collumn, T* newCell)
	{
		if (IsCellValide(row, collumn))
		{
			if (tab[row][collumn] != nullptr)
			{
				delete tab[row][collumn];
			}
			tab[row][collumn] = newCell;
			return true;
		}
		return false;
	}

	template<typename T, int H, int W>
	inline bool Grid<T, H, W>::moveCell(int oldRow, int oldCollumn, int newRow, int newCollumn)
	{
		if (!IsCellValide(oldRow, oldCollumn) || !IsCellValide(newRow, newCollumn))
			return false;

		if (tab[oldRow][oldCollumn] == nullptr || tab[newRow][newCollumn] != nullptr)
			return false;

		tab[newRow][newCollumn] = tab[oldRow][oldCollumn];
		tab[oldRow][oldCollumn] = nullptr;
		return true;
	}

	template<typename T, int H, int W>
	inline bool Grid<T, H, W>::removeCell(int row, int column)
	{
		if (IsCellValide(row, column) && tab[row][column] != nullptr)
		{
			delete tab[row][column];
			tab[row][column] = nullptr;
			return true;
		}
		return false;
	}

	template<typename T, int H, int W>
	inline bool Grid<T, H, W>::isEmpty(int row, int column) const
	{
		if (!IsCellValide(row, column)) return false;
		return tab[row][column] == nullptr;
	}

	template<typename T, int H, int W>
	inline void Grid<T, H, W>::clear()
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (tab[i][j] != nullptr)
				{
					delete tab[i][j];
					tab[i][j] = nullptr;
				}
			}
		}
	}

	template <typename T, int H, int W>
	inline bool Grid<T, H, W>::IsCellValide(int row, int collumn) const
	{
		bool isRowValide = row >= 0 && row < HEIGHT;
		bool isCollumnValide = collumn >= 0 && collumn < WIDTH;
		return isRowValide && isCollumnValide;
	}

}