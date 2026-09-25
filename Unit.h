#pragma once
#include "Cell.h"
class Unit : public Cell{
public:
	virtual void move() = 0;
};

