#pragma once

// IGrid sert d'interface pour toutes les implémentations du template Grid, ça permet une abstraction de l'utilisation des grilles par Game.

// Principe "Type Erasure" appliqué. On masque aux autres classes la gestion des paramètres H et W car cette responsabilitée revient à la grille elle même selon sa version. 
// Les différentes versions de Grid seront donc manipulés uniformément par Game, grâce à des méthodes virtuelles.

namespace GridSystem {

	template<typename T>
	class IGrid
	{
	public:
		virtual ~IGrid() = default;

		virtual T* getCell(int row, int collumn) const = 0;
		virtual bool setCell(int row, int collumn, T* newCell) = 0;
		virtual bool moveCell(int oldRow, int oldCollumn, int newRow, int newCollumn) = 0;
		virtual bool removeCell(int row, int column) = 0;
		virtual bool isEmpty(int row, int column) const = 0;
		virtual void clear() = 0;
		virtual int getHeight() const = 0;
		virtual int getWidth() const = 0;
	};

}