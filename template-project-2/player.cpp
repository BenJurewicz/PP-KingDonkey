#include "player.hpp"

// Point(x, y) is the location of the platform
// Entity(xLeft, xRight, yUp, yDown) is the mask of the payers's standing sprite in global bit map
Player::Player(int _x, int _y) : Point(_x, _y), Entity(/*3, 39, 421, 471*/), standingS(3, 39, 421, 471), jumpingS(3, 51, 549, 594), runningS(116, 161, 423, 471), climbingS(226, 265, 423, 471){
	yVelocity = GRAVITY_MAX;

	sprite = standingS;

	// hithox width and height
	width = sprite.width();
	height = sprite.height();

	state = States::standing;
	direction = Directions::right;

	xVelocity = 0;
	yMoveRemainder = 0;
	xMoveRemainder = 0;

	collidingLadderUpperY = 0;
	collidingLadderBottomY = 0;
	colldingLadderLeftX = 0;

	isJumping = false;
	isOnLadder = false;
	isOnGround = true;
	isImmortal = false;

	isWantingToClimb = false;
	isCollWithLadder = false;
	isWantingToClimbUp = false;
	isWantingToClimbDown = false;
}

void Player::setX(int _x){
	if(_x + sprite.width() > SCREEN_WIDTH){
		x = SCREEN_WIDTH - sprite.width();
	} else if(_x < 0){
		x = 0;
	} else{
		x = _x;
	}
}

void Player::setY(int _y){
	if(_y < 0){
		y = 0;
	} else if(_y + sprite.height() > SCREEN_HEIGHT){
		y = SCREEN_HEIGHT - sprite.height();
	} else{
		y = _y;
	}
}

void Player::xMoveBy(double _x){
	int roundedX = (int)floor(_x);
	xMoveRemainder += _x - roundedX;

	int roundedRemainder = 0;
	if(xMoveRemainder >= 1){
		roundedRemainder = (int)floor(xMoveRemainder);
		xMoveRemainder -= roundedRemainder;
		roundedX += roundedRemainder;
	}

	setX(x + roundedX);
}

void Player::yMoveBy(double _y){
	int roundedY = (int)floor(_y);
	yMoveRemainder += _y - roundedY;

	int roundedRemainder = 0;
	if(yMoveRemainder >= 1){
		roundedRemainder = (int)floor(yMoveRemainder);
		yMoveRemainder -= roundedRemainder;
		roundedY += roundedRemainder;
	}

	setY(y + roundedY);
}

void Player::stopX(){
	xVelocity = 0;
}

void Player::moveRight(){
	xVelocity = PLAYER_STANDART_VELOCITY;
}

void Player::moveLeft(){
	xVelocity = -1 * PLAYER_STANDART_VELOCITY;
}

void Player::wantsToClimb(){
	isWantingToClimb = true;
}

void Player::wantsToClimbUp(){
	isWantingToClimbDown = false;
	isWantingToClimbUp = true;
}

void Player::wantsToClimbDown(){
	if(y + height >= collidingLadderBottomY){
		isOnLadder = false;
		return;
	}
	isWantingToClimbUp = false;
	isWantingToClimbDown = true;
}

void Player::stopClimbing(){
	if(isWantingToClimbUp || isWantingToClimbDown){
		yVelocity = 0;
	}
	isWantingToClimbUp = false;
	isWantingToClimbDown = false;
}

void Player::jump(){
	if(isJumping || isOnLadder || !isOnGround){
		// if we are on ladder and we want to jump we simply fall of the ladder
		isOnLadder = false;
		return;
	}

	isJumping = true;
	yVelocity = PLAYER_JUMP_VELOCITY;
}

double Player::clamp(double num, double min, double max){
	if(num >= max){
		return max;
	} else if(num <= min){
		return min;
	} else{
		return num;
	}
}

void Player::falling(double deltaTime){
	if(isOnLadder){
		return;
	}

	if(isOnGround){
		yVelocity = GRAVITY_MAX;
		return;
	}

	yVelocity += GRAVITY_ACCELERATION * deltaTime;
	yVelocity = clamp(yVelocity, PLAYER_JUMP_VELOCITY, GRAVITY_MAX);
}

void Player::update(double deltaTime, double worldTime, PlatformArray& platforms, LadderArray& ladders, BarrelArray& barrels, bool& barrelPlayerCollision){
	isOnGround = false;

	checkForLadders(ladders);
	if(isCollWithLadder == false){
		isOnLadder = false;
	} else if(isWantingToClimbUp || isWantingToClimbDown){
		isOnLadder = true;
		x = colldingLadderLeftX + LADDER_SPRITE_WIDTH/2 - climbingS.width()/2;
		tryClimbing();
	}

	if(isOnLadder == false){
		xMoveBy(xVelocity * deltaTime);
		//resolvePlatformCollisions(platforms, xVelocity, 0);
		resolvePlatformCollisionsX(platforms, xVelocity);
	}

	yMoveBy(yVelocity * deltaTime);
	resolvePlatformCollisionsY(platforms, yVelocity);
	falling(deltaTime);

	updateIsImmortal(worldTime);
	resolveBarrelCollsions(barrels, barrelPlayerCollision);

	updateState();
	updateDirection();

	animate(worldTime);
}

void Player::updateState(){
	if(isOnLadder){
		state = climbing;
	} else if(isJumping || !isOnGround){
		state = jumping;
	} else if((int)xVelocity != 0){
		state = running;
	} else if((int)xVelocity == 0){
		state = standing;
	}
}

void Player::updateDirection(){
	if(xVelocity > 0){
		direction = right;
	} else if(xVelocity < 0){
		direction = left;
	}
}

void Player::animate(double worldTime){
	switch(state){
		case Player::running:
			sprite = runningS;
			break;
		case Player::jumping:
			sprite = jumpingS;
			break;
		case Player::climbing:
			sprite = climbingS;
			break;
		case Player::standing:
			sprite = standingS;
			break;
		default:
			break;
	}

	if(direction == right && state != climbing){
		sprite.xLeft += 55;
		sprite.xRight += 55;
	}

	if(state == running && (int)(worldTime * 10)%2==0){
		sprite.yUp = runningS.yUp + 63;
		sprite.yDown = runningS.yDown + 63;
	}

	if(state == climbing && (int)(worldTime * 10)%2==0 && yVelocity != 0){
		sprite.yUp = climbingS.yUp + 63;
		sprite.yDown = climbingS.yDown + 63;
	}
}

void Player::tryClimbing(){
	if(isWantingToClimbUp && isOnLadder){
		yVelocity = -1 * PLAYER_LADDER_CLIMBING_SPEED;
	} else if(isWantingToClimbDown && isOnLadder){
		yVelocity = PLAYER_LADDER_CLIMBING_SPEED;
	}
}

void Player::checkForLadders(LadderArray& ladders){
	isCollWithLadder = false;
	for(int i = 0; i < ladders.len(); i++){
		Ladder* ladder = ladders.get(i);
		if(ladder == NULL){
			return;
		}
		if(isColliding(ladder)){
			resolveLadderCollision(ladder);
		}
	}
}

void Player::resolveLadderCollision(Ladder* ladder){
	colldingLadderLeftX = ladder->x;
	collidingLadderUpperY = ladder->y;
	collidingLadderBottomY = ladder->y + ladder->height;
	isCollWithLadder = true;
}

void Player::resolvePlatformCollisionsX(PlatformArray& platforms, double xVel){
	for(int i = 0; i < platforms.len(); i++){
		Platform* platform = platforms.get(i);
		if(platform == NULL){
			return;
		}
		if(isColliding(platform)){
			resolvePlatformCollisionX(platform, xVel);
		}
	}
}

void Player::resolvePlatformCollisionsY(PlatformArray& platforms, double yVel){
	for(int i = 0; i < platforms.len(); i++){
		Platform* platform = platforms.get(i);
		if(platform == NULL){
			return;
		}
		if(isColliding(platform)){
			resolvePlatformCollisionY(platform, yVel);
		}
	}
}

void Player::resolvePlatformCollisionX(Platform* platform, double xVel){
	if(xVel > 0){
		// colliding with platform from the right
		setX(platform->x - width);
	}
	if(xVel < 0){
		// colliding with platform from the left
		setX(platform->x + platform->width);
	}
}

void Player::resolvePlatformCollisionY(Platform* platform, double yVel){
	if(yVel > 0){
		// coliding with platform while falling (moving down)
		if(isOnLadder && y <= collidingLadderUpperY + PLATFORM_SPRITE_HEIGHT){
			return;
		} else if(isOnLadder && y + height >= collidingLadderBottomY){
			isOnLadder = false;
			isWantingToClimbDown = false;
		}

		isJumping = false;
		isOnGround = true;
		//isWantingToClimbDown = false;
		setY(platform->y - height);
	}
	if(yVel < 0){
		// colliding with platform while jumping (moving up)
		if(isOnLadder){
			int playerBottomY = y + height;
			int platformTopY = platform->y;
			if(playerBottomY > platformTopY){
				return;
			}
		}
		yVelocity *= -1; // start falling when we hit a celling
		setY(platform->y + platform->height);
	}
}

void Player::resolveBarrelCollsions(BarrelArray& barrels, bool& barrelPlayerCollision){
	barrelPlayerCollision = false;
	if(isImmortal){
		return;
	}
	for(int i = 0; i < barrels.len(); i++){
		Barrel* barrel = barrels.get(i);
		if(barrel == NULL){
			return;
		}
		if(isColliding(barrel)){
			resolveBarrelCollsion(barrelPlayerCollision);
		}
	}
}

void Player::resolveBarrelCollsion(bool& barrelPlayerCollision){
	barrelPlayerCollision = true;
	isImmortal = true;
	//printf("Collision with barrel detected.\n");
}

void Player::updateIsImmortal(double worldTime){
	if(worldTime - lastBarrelCollsion < PLAYER_IMMORTALITY_PERIOD){
		return;
	}
	lastBarrelCollsion = worldTime;

	isImmortal = false;
}