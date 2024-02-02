#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "point.hpp"

class RectangleHitbox;
class CircleHitbox;

class Hitbox : virtual public Point{
public:
	Hitbox(int xPos, int yPos);
	virtual bool isColliding(RectangleHitbox* rect) = 0;
	virtual bool isColliding(CircleHitbox* circle) = 0;
	bool isColliding(Hitbox* hitbox);
};

class RectangleHitbox : public Hitbox{
public:
	int width;
	int height;
	RectangleHitbox(int xPos, int yPos, int width, int height);
	RectangleHitbox(int width, int height);
	RectangleHitbox();
	bool isColliding(RectangleHitbox* rect) override;
	bool isColliding(CircleHitbox* circle) override;
};

class CircleHitbox : public Hitbox{
	double clamp(double num, double min, double max);
	double doubleAbs(double num);
public:
	double radius;
	CircleHitbox(int xPos, int yPos, double radius);
	CircleHitbox(double radius);
	CircleHitbox();

	double getCenterX();
	double getCenterY();
	double getDistanceFromCenter(double _x, double _y);

	bool isColliding(RectangleHitbox* rect) override;
	bool isColliding(CircleHitbox* circle) override;
};