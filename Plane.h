#pragma once
#include "Unit.h"

class Plane : public Unit
{
public:
	static constexpr char SYMBOL = '|';
	static constexpr int MAX_HEALTH = 100;
	static constexpr int BASE_ATTACK = 20;
	static constexpr int BASE_MOVE_POWER = 1;
	static constexpr int BASE_ATTACK_RANGE = 3;


	Plane(Player* p_owner) :
		Unit(p_owner, MAX_HEALTH, BASE_ATTACK, BASE_MOVE_POWER, BASE_ATTACK_RANGE, SYMBOL) {
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

	std::vector<Position2D> SimulateAttack(Direction direction, Position2D currentPos) const override
	{
		std::vector<Position2D> hitPositions;

		if (direction == Direction::Up)
		{
			for (int i = 1; i <= attackRange; ++i)
				hitPositions.push_back({currentPos.row - i, currentPos.col});
		}
		else if (direction == Direction::Down)
		{
			for (int i = 1; i <= attackRange; ++i)
				hitPositions.push_back({currentPos.row + i, currentPos.col});
		}

		return hitPositions;
	}
};

