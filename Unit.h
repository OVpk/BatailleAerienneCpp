#pragma once
#include "Target.h"
#include "Movements.h"

class Unit : public Target
{
protected:
	int health;
	int attackDmg;
	int movePower;

public:
	Unit(Player* p_owner, int p_health, int p_attackDmg, int p_movePower, char p_symbol):
		Target(p_owner, p_symbol), health(p_health), attackDmg(p_attackDmg), movePower(p_movePower) {}

	~Unit() override = default;

	int GetHealth() const {return health;}
	int GetAttack() const {return attackDmg;}

	virtual std::optional<Position2D> SimulateMove(Direction direction, Position2D currentPos) const = 0;
};

