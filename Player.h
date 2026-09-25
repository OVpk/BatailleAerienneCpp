#pragma once
#include "Unit.h"

#include <iostream>

class Player
{
public:
	const std::string color;

	Unit* units[];

	Player(std::string p_color) : color(p_color){

	}

};

