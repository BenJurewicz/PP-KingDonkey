#pragma once

#include "point.hpp"
#include "hitbox.hpp"
#include "entity.hpp"
#include "sdl.hpp"

class Ladder : public Entity, public RectangleHitbox, virtual public Point{
public:
	int lenght;
	Ladder(int x, int y, int _lenght);
	Ladder();
};

class LadderArray{
	size_t lenght;
	Ladder** table;
	size_t _i;
	bool inRange(size_t index);
public:
	LadderArray(size_t _len);
	~LadderArray();
	size_t len();
	Ladder* get(size_t index);
	void add(int x, int y, int _lenght);
	void add2(Ladder* platform);
	void drawAll(Sdl& sdl);
	void drawAllHitboxes(Sdl& sdl);
};