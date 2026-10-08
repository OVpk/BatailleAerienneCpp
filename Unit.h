#pragma once
#include "Target.h"
#include "Movements.h"
#include <vector>

class Unit : public Target
{
protected:
	int attackDmg;
	int movePower;
	int attackRange;

public:
	Unit(Player* p_owner, int p_health, int p_attackDmg, int p_movePower, int p_attackRange, char p_symbol):
		Target(p_owner, p_health, p_symbol), attackDmg(p_attackDmg), movePower(p_movePower), attackRange(p_attackRange) {}

	~Unit() override = default;

	int GetAttack() const {return attackDmg;}
	int GetAttackRange() const {return attackRange;}

	virtual std::optional<Position2D> SimulateMove(Direction direction, Position2D currentPos) const = 0;
	virtual std::vector<Position2D> SimulateAttack(Direction direction, Position2D currentPos) const = 0;
};

