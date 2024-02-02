#pragma once

#include "hitbox.hpp"
#include "point.hpp"

class WinningArea : public RectangleHitbox, virtual public Point{
public:
	WinningArea(int _x, int _y, int _width, int _height);
};