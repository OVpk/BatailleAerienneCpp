#pragma once
#include "Unit.h"

class Drone : public Unit
{
public:
	static constexpr char SYMBOL = 'X';
	static constexpr int MAX_HEALTH = 50;
	static constexpr int BASE_ATTACK = 10;
	static constexpr int BASE_MOVE_POWER = 1;
	static constexpr int BASE_ATTACK_RANGE = 1;

	Drone(Player* p_owner) :
		Unit(p_owner, MAX_HEALTH, BASE_ATTACK, BASE_MOVE_POWER, BASE_ATTACK_RANGE, SYMBOL) {
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

	std::vector<Position2D> SimulateAttack(Direction direction, Position2D currentPos) const override
	{
		std::vector<Position2D> hitPositions;
		int dirRow = 0;
		int dirCollumn = 0;

		switch (direction)
		{
		case Direction::Up:			dirRow = -1; dirCollumn = 0;  break;
		case Direction::Down:		dirRow = 1; dirCollumn = 0;  break;
		case Direction::Left:		dirRow = 0; dirCollumn = -1; break;
		case Direction::Right:		dirRow = 0; dirCollumn = 1;  break;
		case Direction::TopLeft:	dirRow = -1; dirCollumn = -1; break;
		case Direction::TopRight:	dirRow = -1; dirCollumn = 1;  break;
		case Direction::BottomLeft:	dirRow = 1; dirCollumn = -1; break;
		case Direction::BottomRight:dirRow = 1; dirCollumn = 1;  break;
		}

		for (int i = 1; i <= attackRange; ++i)
		{
			hitPositions.push_back({currentPos.row + (dirRow * i), currentPos.col + (dirCollumn * i)});
		}

		return hitPositions;
	}
};