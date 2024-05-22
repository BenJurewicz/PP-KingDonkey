#pragma once

class Sprite{
public:
	int xLeft;
	int xRight;
	int yUp;
	int yDown;


	int width();
	int height();

	Sprite();
	Sprite(int _xLeft, int _xRight, int _yUp, int _yDown);
};