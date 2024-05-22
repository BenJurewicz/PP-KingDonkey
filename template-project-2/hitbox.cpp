#include "hitbox.hpp"

Hitbox::Hitbox(int xPos, int yPos) : Point(xPos, yPos){}

bool RectangleHitbox::isColliding(RectangleHitbox* rect){
	//printf("rect-rect\n");
	int AxLeft = x;
	int AxRight = x + width;
	int AyUp = y;
	int AyDown = y + height;

	int BxLeft = rect->x;
	int BxRight = rect->x + rect->width;
	int ByUp = rect->y;
	int ByDown = rect->y + rect->height;

	//check if there is collision using AABB
	if(AxLeft < BxRight &&
	   AxRight > BxLeft &&
	   AyUp < ByDown &&
	   AyDown > ByUp){
		return true;
	}
	return false;
}

bool RectangleHitbox::isColliding(CircleHitbox* circle){
	//printf("rect-circle\n");
	return circle->isColliding(this);
}

bool CircleHitbox::isColliding(RectangleHitbox* rect){
	/*printf("rect-circ\n");*/
	double clampededCenterX = clamp(getCenterX(), rect->x, rect->x + rect->width);
	double clampededCenterY = clamp(getCenterY(), rect->y, rect->y + rect->height);

	double distanceFromCenter = getDistanceFromCenter(clampededCenterX, clampededCenterY);

	if(distanceFromCenter < radius){
		// colliding
		return true;
	} else{
		// not colliding
		return false;
	}
}

bool CircleHitbox::isColliding(CircleHitbox* circle){
	printf("circ-circ\n");
	return false;
}

bool Hitbox::isColliding(Hitbox* hitbox){
	printf("general-collision\n");
	return false;
}

RectangleHitbox::RectangleHitbox(int xPos, int yPos, int _width, int _height) : Hitbox(xPos, yPos){
	width = _width;
	height = _height;
}

RectangleHitbox::RectangleHitbox(int width, int height) : RectangleHitbox(0, 0, width, height){}

RectangleHitbox::RectangleHitbox() : RectangleHitbox(0, 0, 0, 0){};

CircleHitbox::CircleHitbox(int xPos, int yPos, double _radius) : Hitbox(xPos, yPos){
	radius = _radius;
}

CircleHitbox::CircleHitbox(double radius) : CircleHitbox(0, 0, radius){}

CircleHitbox::CircleHitbox() : CircleHitbox(0, 0, 0){}

double CircleHitbox::doubleAbs(double num){
	return num >= 0 ? num : -1 * num;
}

double CircleHitbox::getCenterX(){
	return x + radius - 0.5;
}

double CircleHitbox::getCenterY(){
	return y + radius - 0.5;
}

double CircleHitbox::getDistanceFromCenter(double _x, double _y){
	int xVector = doubleAbs(getCenterX() - _x);
	int yVector = doubleAbs(getCenterY() - _y);

	int xVecSquared = xVector * xVector;
	int yVecSquared = yVector * yVector;

	return sqrt(xVecSquared + yVecSquared);
}

double CircleHitbox::clamp(double num, double min, double max){
	if(num >= max){
		return max;
	} else if(num <= min){
		return min;
	} else{
		return num;
	}
}