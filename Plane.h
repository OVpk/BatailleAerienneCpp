#pragma once
#include "Unit.h"

class Plane : public Unit
{
public:
	static constexpr char SYMBOL = '|';
	static constexpr int MAX_HEALTH = 100;
	static constexpr int BASE_ATTACK = 20;
	static constexpr int BASE_MOVE_POWER = 1;


	Plane(Player* p_owner) :
		Unit(p_owner, MAX_HEALTH, BASE_ATTACK, BASE_MOVE_POWER, SYMBOL) {
	}

	std::optional<Position2D> SimulateMove(Direction direction, Position2D currentPos) const override
	{
		switch (direction)
		{
		case Direction::Up:		return Position2D{currentPos.row - movePower, currentPos.col};
		case Direction::Down:	return Position2D{currentPos.row + movePower, currentPos.col};
		case Direction::Left:	return Position2D{currentPos.row, currentPos.col - movePower};
		case Direction::Right:	return Position2D{currentPos.row, currentPos.col + movePower};
		default:
			return std::nullopt;
		}
	}
};

