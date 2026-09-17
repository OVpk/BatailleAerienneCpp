#include <iostream>
#include <random>
#include "Grid.h"
#include "GridRenderer.h"

int main() {

	Grid* grille = new Grid();

	GridRenderer* renderer = new GridRenderer();

	renderer->DrawGrid(grille);

	return 0;
}