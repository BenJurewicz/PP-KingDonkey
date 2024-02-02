#pragma once

#include "entity.hpp"
#include "hitbox.hpp"
#include "point.hpp"
#include "sdl.hpp"

// this class is made with the asumption that
// the platforms arent tilted
class Platform : public Entity, public RectangleHitbox, virtual public Point{
public:
	int lenght;
	Platform(int x, int y, int _lenght);
	Platform();
};

class PlatformArray{
	size_t lenght;
	Platform** table;
	size_t _i;
	bool inRange(size_t index);
public:
	PlatformArray(size_t _len);
	~PlatformArray();
	size_t len();
	Platform* get(size_t index);
	void add(int x, int y, int _lenght);
	void drawAll(Sdl& sdl);
	void drawAllHitboxes(Sdl& sdl);
};