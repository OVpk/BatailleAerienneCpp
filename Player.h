#pragma once

#include <iostream>

class Player
{
public:
	std::string_view color;

	Player(std::string_view p_color) : color(p_color){

	}

};

