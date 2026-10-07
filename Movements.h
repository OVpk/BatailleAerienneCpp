#pragma once
#include <optional>

enum class Direction
{
    Up,
    Down,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

struct Position2D
{
    int row;
    int col;
};