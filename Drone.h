#pragma once
#include "Unit.h"

class Drone : public Unit
{
public:
	static constexpr char SYMBOL = 'X';
	static constexpr int MAX_HEALTH = 50;
	static constexpr int BASE_ATTACK = 10;
	static constexpr int BASE_MOVE_POWER = 1;

	Drone(Player* p_owner) :
		Unit(p_owner, MAX_HEALTH, BASE_ATTACK, BASE_MOVE_POWER, SYMBOL) {
	}

	std::optional<Position2D> SimulateMove(Direction direction, Position2D currentPos) const override
	{
		switch (direction)
		{
		case Direction::TopLeft:		return Position2D{currentPos.row - movePower, currentPos.col - movePower};
		case Direction::TopRight:		return Position2D{currentPos.row - movePower, currentPos.col + movePower};
		case Direction::BottomLeft:		return Position2D{currentPos.row + movePower, currentPos.col - movePower};
		case Direction::BottomRight:	return Position2D{currentPos.row + movePower, currentPos.col + movePower};
		default:
			return std::nullopt;
		}
	}
};