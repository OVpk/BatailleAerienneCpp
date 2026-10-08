#pragma once
#include "Player.h"
#include "IRenderableCell.h"

class Target : public GridSystem::IRenderableCell
{
private:
	static constexpr int MAX_HEALTH = 100;

	const char symbol;
	const Player* owner;
	int health;

public:
	Target(Player* p_owner, int p_health = MAX_HEALTH, char p_symbol = 'T') :
		owner(p_owner), health(p_health), symbol(p_symbol) {}

	~Target() override = default;


	const Player* GetOwner() const { return owner; };
	int GetHealth() const { return health; }

	char getSymbol() const override final {return symbol;}
	std::string_view getColor() const override {return owner->color;}

	void TakeDamage(int damage)
	{
		health -= damage;
		if (health < 0) health = 0;
	}
};

