#pragma once

#include <math.h>

#include "point.hpp"
#include "entity.hpp"
#include "hitbox.hpp"
#include "platform.hpp"

class Barrel : public Entity, public CircleHitbox, virtual public Point{
	double xVelocity;
	double yVelocity;
	double yMoveRemainder;
	double xMoveRemainder;
	double lastAnimationChange;
	double animationSpacing;
	bool isOnGround;

	enum Directions{
		left,
		right,
		none
	};
	Directions direction;
	int animationState;

	double clamp(double num, double min, double max);
	int modulo(int num, int modBase);

	void animate(double worldTime);
	void updateDirectionAndVelocity(double worldTime);


	void xMoveBy(double _x);
	void yMoveBy(double _y);

	void setX(int _x);
	void setY(int _y);

	void resolvePlatformCollision(Platform* platform, double xVel, double yVel);
	void resolvePlatformCollisions(PlatformArray& platforms, double xVel, double yVel);
public:
	Barrel(int _x, int _y, bool startsGoingRight, double worldTime);
	void update(double deltaTime, double worldTime, PlatformArray& platforms);
};

class BarrelArray{
	size_t lenght;
	Barrel** table;
	size_t _i;
	bool inRange(size_t index);
	double lastSpawnTime;
	int spawnCordX;
	int spawnCordY;
public:
	BarrelArray(size_t _len, int spawnPointX = 0, int spawnPointY = 0);
	~BarrelArray();
	size_t len();
	Barrel* get(size_t index);
	void spawnNew(double worldTime);
	void updateAll(double deltaTime, double worldTime, PlatformArray& platforms);
	void add(int x, int y, bool startsGoingRight, double worldTime);
	void drawAll(Sdl& sdl);
	void drawAllHitboxes(Sdl& sdl);
};