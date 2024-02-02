#pragma once

#include <stdio.h>
#include <string.h>

extern "C" {
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#include "entity.hpp"
#include "hitbox.hpp"
#include "globals.hpp"

struct Colors{
	int czarny;
	int zielony;
	int czerwony;
	int niebieski;
	int jasnyNiebieski;
};

class Sdl{

	SDL_Window* window;
	SDL_Surface* charset;
	SDL_Texture* scrtex; // screen texture
	SDL_Renderer* renderer;
	SDL_Surface* screen;
	SDL_Event event;

	double lastTick;
	double fpsTimer;
	int frames;
	int fps; // fps was float originally
	int xMouse;
	int yMouse;

	void createWindowAndRenderer();
	void setMiscellaneous();
	void createScreen();
	void createScreenTexture();
	void loadCharset();
	void loadGlobalBitMap();
	void initColors();

	// rysowanie pojedynczego pixela
	// draw a single pixel
	void drawPixel(int x, int y, Uint32 color);

	// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1)
	// b¹dŸ poziomie (gdy dx = 1, dy = 0)
	// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0)
	// line
	void drawLine(int x, int y, int l, int dx, int dy,
				  Uint32 color);

	// set the values of mask and dest
	// used in Sdl::drawEntity()
	void setRectValues(SDL_Rect& mask, int x, int y, int width, int height);

	// moves the dest by entityWidth*xMove to the right and by entityHeight*yMove down
	// used in Sdl::drawEntity()
	void moveDest(SDL_Rect& dest, int entityWidth, int entityHeight, int xMove = 1, int yMove = 1);


	double doubleMin(double x, double y);
public:

	// holds a big bmp file with all of the used textures
	SDL_Surface* globalBitMap;

	// some predefined custom colors
	Colors colors;

	int getScreenWidth();
	int getScreenHeight();

	// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
	// charset to bitmapa 128x128 zawieraj¹ca znaki
	// draw a text txt on surface screen, starting from the point (x, y)
	// charset is a 128x128 bitmap containing character images
	void drawString(int x, int y, const char* text);

	// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
	// (x, y) to punkt œrodka obrazka sprite na ekranie
	// draw a surface sprite on a surface screen in point (x, y)
	// (x, y) is the center of sprite on screen
	void drawSurface(SDL_Surface* sprite, int x, int y);

	// rysowanie prostok¹ta o d³ugoœci boków l i k
	// draw a rectangle of size l by k
	void drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

	// draws the sprite of an entity at its location
	void drawEntity(Entity entity);

	// draw the hitbox of the entity
	void drawHitbox(Hitbox* hitbox);
	void drawHitbox(RectangleHitbox* hitbox);
	void drawHitbox(CircleHitbox* hitbox);

	// renders current buffer to the screen
	void refreshScreen();

	// fills the screen with black
	void clearScreen();

	void printMouseCords(Sdl& sdl, bool& mouseMoved);

	double getDeltaTime();
	int getFps(double deltaTime);

	Sdl();
	~Sdl();
};