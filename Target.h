#pragma once
#include "Player.h"
#include "IRenderableCell.h"

class Target : public GridSystem::IRenderableCell
{
private:
	const char symbol;
	const Player* owner;

public:
	Target(Player* p_owner, char p_symbol = 'T') :
		owner(p_owner), symbol(p_symbol) {}

	~Target() override = default;


	const Player* GetOwner() const { return owner; };

	char getSymbol() const override final {return symbol;}
	std::string_view getColor() const override {return owner->color;}

};

