#include "barrel.hpp"

Barrel::Barrel(int _x, int _y, bool startsGoingRight, double worldTime) : Entity(534, 570, 498, 534), CircleHitbox((35+2)/2), Point(_x, _y){
	animationState = 0;
	direction = startsGoingRight ? right : left;

	xVelocity = BARREL_STANDART_VELOCITY * (startsGoingRight ? 1 : -1);
	yVelocity = GRAVITY_MAX;

	xMoveRemainder = 0;
	yMoveRemainder = 0;

	isOnGround = false;

	animationSpacing = 0.12; // in seconds
	lastAnimationChange = worldTime;
}

void Barrel::update(double deltaTime, double worldTime, PlatformArray& platforms){
	isOnGround = false;

	xMoveBy(xVelocity * deltaTime);
	resolvePlatformCollisions(platforms, xVelocity, 0);

	yMoveBy(yVelocity * deltaTime);
	resolvePlatformCollisions(platforms, 0, yVelocity);

	updateDirectionAndVelocity(worldTime);
	animate(worldTime);
	//printf("direction %d\n", direction);
}

void Barrel::animate(double worldTime){
	if(worldTime - lastAnimationChange < animationSpacing){
		return;
	}

	lastAnimationChange = worldTime;

	int incrementAnimation;
	if(direction == left){
		incrementAnimation = -1;
	} else if(direction == right){
		incrementAnimation = 1;
	} else{
		incrementAnimation = 0;
	}

	animationState = modulo(animationState + incrementAnimation, 4);

	int distanceBetweenSprites = 51; // px
	int startingxLeft = 534; // px
	int startingxRight = 569; // px
	sprite.xLeft = startingxLeft + animationState * distanceBetweenSprites;
	sprite.xRight = startingxRight + animationState * distanceBetweenSprites;
}

void Barrel::updateDirectionAndVelocity(double worldTime){
	if(x >= SCREEN_WIDTH - 2 * radius || x <= 0){
		xVelocity *= -1;
	}

	if(xVelocity > 0){
		direction = right;
	} else if(xVelocity < 0){
		direction = left;
	} else{
		direction = none;
	}
}

int Barrel::modulo(int num, int modBase){
	// we need to implement our own modulo operator as
	// we want the negative numbers to loop back to the upper values
	// ex. modulo(-1, 2) should equal 1
	// not -1 as it is in the divisionRemainder(%) operator
	return (num%modBase + modBase)%modBase;
}

double Barrel::clamp(double num, double min, double max){
	if(num >= max){
		return max;
	} else if(num <= min){
		return min;
	} else{
		return num;
	}
}

void Barrel::setX(int _x){
	if(_x + sprite.width() > SCREEN_WIDTH){
		x = SCREEN_WIDTH - sprite.width();
	} else if(_x < 0){
		x = 0;
	} else{
		x = _x;
	}
}

void Barrel::setY(int _y){
	if(_y < 0){
		y = 0;
	} else if(_y + sprite.height() > SCREEN_HEIGHT){
		y = SCREEN_HEIGHT - sprite.height();
	} else{
		y = _y;
	}
}

void Barrel::xMoveBy(double _x){
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

void Barrel::yMoveBy(double _y){
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

void Barrel::resolvePlatformCollisions(PlatformArray& platforms, double xVel, double yVel){
	for(int i = 0; i < platforms.len(); i++){
		Platform* platform = platforms.get(i);
		if(platform == NULL){
			return;
		}
		if(isColliding(platform)){
			resolvePlatformCollision(platform, xVel, yVel);
		}
	}
}

void Barrel::resolvePlatformCollision(Platform* platform, double xVel, double yVel){

	if(xVel > 0){
		// colliding with platform from the right
		setX(platform->x - (int)(2*radius));
	}
	if(xVel < 0){
		// colliding with platform from the left
		setX(platform->x + platform->width);
	}
	if(xVel != 0){
		// colliding with platform from left or right
		xVelocity *= -1;
	}

	if(yVel > 0){
		// coliding with platform while falling
		isOnGround = true;
		//setY(platform->y - height);
		setY(platform->y - (int)(2*radius));
	}
	if(yVel < 0){
		setY(platform->y + platform->height);
	}

}

BarrelArray::BarrelArray(size_t _len, int spawnPointX, int spawnPointY){
	table = (Barrel**)calloc(_len, sizeof(Barrel*));
	lenght = _len;
	lastSpawnTime = 0;
	_i = 0;
	spawnCordX = spawnPointX%(SCREEN_WIDTH - BARREL_SPRITE_WIDTH);
	spawnCordY = spawnPointY%(SCREEN_HEIGHT - BARREL_SPRITE_HEIGHT);
}

BarrelArray::~BarrelArray(){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			continue;
		}
		delete table[i];
	}

	free(table);
}

size_t BarrelArray::len(){
	return lenght;
}

bool BarrelArray::inRange(size_t index){
	return 0 <= index && index < lenght;
}

Barrel* BarrelArray::get(size_t index){
	if(inRange(index)){
		return table[index];
	}
	return NULL;
}

void BarrelArray::add(int x, int y, bool startsGoingRight, double worldTime){
	if(inRange(_i)){
		table[_i] = new Barrel(x, y, startsGoingRight, worldTime);
		_i++;
	}
}

void BarrelArray::drawAllHitboxes(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawHitbox(table[i]);
	}
}

void BarrelArray::drawAll(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawEntity(*table[i]);
	}
}

void BarrelArray::updateAll(double deltaTime, double worldTime, PlatformArray& platforms){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		table[i]->update(deltaTime, worldTime, platforms);
	}
}

void BarrelArray::spawnNew(double worldTime){
	if(worldTime - lastSpawnTime < BARREL_SPAWN_PERIOD){
		return;
	}
	lastSpawnTime = worldTime;

	bool directionRight = rand()%2==1 ? true : false;

	if(BARREL_RANDOM_SPAWN){
		spawnCordX = rand()%(SCREEN_WIDTH - BARREL_SPRITE_WIDTH);
		spawnCordY = 10;
	}

	Barrel** barrel = &table[_i];
	_i = (_i + 1)%lenght;
	if(barrel != NULL){
		delete* barrel;
	}
	*barrel = new Barrel(spawnCordX, spawnCordY, directionRight, worldTime);
}