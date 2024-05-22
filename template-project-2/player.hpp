#pragma once

#include <stdio.h>
#include <math.h>

#include "entity.hpp"
#include "hitbox.hpp"
#include "point.hpp"
#include "platform.hpp"
#include "ladder.hpp"
#include "barrel.hpp"
#include "globals.hpp"

class Player : public Entity, public RectangleHitbox, virtual public Point{
	enum States{
		running,
		jumping,
		climbing,
		standing
	};

	enum Directions{
		left,
		right
	};

	Sprite runningS;
	Sprite jumpingS;
	Sprite climbingS;
	Sprite standingS;

	States state;
	Directions direction;

	double yMoveRemainder;
	double xMoveRemainder;
	double xVelocity;
	double yVelocity;
	double lastBarrelCollsion;

	bool isOnGround;
	bool isJumping;
	bool isOnLadder;
	bool isWantingToClimb;
	bool isCollWithLadder;
	bool isWantingToClimbUp;
	bool isWantingToClimbDown;
	bool isImmortal;

	int collidingLadderUpperY;
	int collidingLadderBottomY;
	int colldingLadderLeftX;

	double clamp(double num, double min, double max);

	void falling(double deltaTime);

	void animate(double worldTime);
	void updateState();
	void updateDirection();

	void updateIsImmortal(double worldTime);

	void xMoveBy(double _x);
	void yMoveBy(double _y);

	void setX(int _x);
	void setY(int _y);

	//void tryClimbing(LadderArray& ladders);
	void tryClimbing();
	void checkForLadders(LadderArray& ladders);
	void resolveLadderCollision(Ladder* ladder);

	void resolvePlatformCollisionX(Platform* platform, double xVel);
	void resolvePlatformCollisionY(Platform* platform, double yVel);
	void resolvePlatformCollisionsX(PlatformArray& platforms, double xVel);
	void resolvePlatformCollisionsY(PlatformArray& platforms, double yVel);

	void resolveBarrelCollsion(bool& barrelPlayerCollision);
	void resolveBarrelCollsions(BarrelArray& barrels, bool& barrelPlayerCollision);
public:

	void stopX();
	void moveRight();
	void moveLeft();

	void jump();

	void update(double deltaTime, double worldTime, PlatformArray& platforms, LadderArray& ladders, BarrelArray& barrels, bool& barrelPlayerCollision);


	void wantsToClimb();
	void wantsToClimbUp();
	void wantsToClimbDown();
	void stopClimbing();

	Player(int _x = 0, int _y = 677);
};