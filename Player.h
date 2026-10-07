#pragma once

#include <iostream>

class Player
{
public:
	const std::string playerName;
	const std::string_view color;

	Player(std::string_view p_name, std::string_view p_color) :
		playerName(p_name), color(p_color)
	{
	}

};

