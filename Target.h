#pragma once
#include "Player.h"
#include "IRenderableCell.h"

class Target : public IRenderableCell
{
private:
	char symbol = 'T';
	const Player* owner;

public:
	Target(Player* p_owner) : owner(p_owner) {}

	~Target() override {}


	const Player* GetOwner() const { return owner; };

	char getSymbol() const override { return symbol; }
	std::string_view getColor() const override { return owner->color; }

};

