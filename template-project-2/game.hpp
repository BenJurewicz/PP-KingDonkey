#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <Windows.h> // remove

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#include "sdl.hpp"
#include "player.hpp"
#include "platform.hpp"
#include "hitbox.hpp"
#include "ladder.hpp"
#include "globals.hpp"
#include "barrel.hpp"
#include "level.hpp"

class Game{
	int quit;
	Sdl sdl; // init the sdl library
	SDL_Event event;
	Levels levels; // load all the levels

	Level* level;
	PlatformArray* platforms;
	LadderArray* ladders;
	BarrelArray* barrels;
	RectangleHitbox* winningArea;
	Player* player;

	// Reset while changing level
	double worldTime;
	double delta;
	bool mouseMoved;
	bool barrelPlayerCollision;
	bool startNewGame;
	bool isInWinningArea;

	void drawInformationRectangle();
	void printBarrelAndWinningAreaCollsion();
	void drawSaticText(double fps);

	void handeInput();
	void handleKeyPressed();
	void handleKeyLetGo();

	void gameLoop();
public:
	Game();
	void programLoop();
};