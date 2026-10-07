#pragma once
#include <string_view>

class IRenderableCell
{
public:
	virtual ~IRenderableCell() = default;

	virtual char getSymbol() const = 0;
	virtual std::string_view getColor() const = 0;
};

