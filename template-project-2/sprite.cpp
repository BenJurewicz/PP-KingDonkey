#include "sprite.hpp"

Sprite::Sprite(int _xLeft, int _xRight, int _yUp, int _yDown) : xLeft(_xLeft), xRight(_xRight), yUp(_yUp), yDown(_yDown){}

Sprite::Sprite() : Sprite(0, 0, 0, 0){}

int Sprite::width(){
	return xRight - xLeft;
}

int Sprite::height(){
	return yDown - yUp;
}