#pragma once

#include "point.hpp"
#include "sprite.hpp"

class Entity : virtual public Point{
public:
	Sprite sprite;
	int YSpriteCount; // how many times the sprites are stacked vertically
	int XSpriteCount; // how many times the sprites are stacked horizontally

	Entity();
	Entity(int xPoint, int yPoint, int _xLeft, int _xRight, int _yUp, int _yDown);
	Entity(int _xLeft, int _xRight, int _yUp, int _yDown);
};