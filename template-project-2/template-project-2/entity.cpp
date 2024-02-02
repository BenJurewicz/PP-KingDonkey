#include "entity.hpp"

Entity::Entity(int xPoint, int yPoint, int _xLeft, int _xRight, int _yUp, int _yDown) : Point(xPoint, yPoint), sprite(_xLeft, _xRight, _yUp, _yDown){
	XSpriteCount = 1;
	YSpriteCount = 1;
}

Entity::Entity(int _xLeft, int _xRight, int _yUp, int _yDown) : Entity(0, 0, _xLeft, _xRight, _yUp, _yDown){}

Entity::Entity() : Entity(0, 0, 0, 0, 0, 0){}