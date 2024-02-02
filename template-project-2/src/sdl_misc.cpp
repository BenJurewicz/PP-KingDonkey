#include "sdl.hpp"

void Sdl::printMouseCords(Sdl& sdl, bool& mouseMoved){
	char text[128];

	if(mouseMoved){
		SDL_GetMouseState(&xMouse, &yMouse);
		mouseMoved = false;
	}

	sprintf_s(
		text,
		"Mouse Cords: x=%d; y=%d",
		xMouse, yMouse);
	if(PRINT_CURSOR_CORDS_TOP_LEFT){
		drawString(SCREEN_WIDTH - (int)strlen(text) * 8 - 10, 10, text);
	}
	if(PRINT_CURSOS_CORDS_NEXT_TO_CURSOR){
		drawString(xMouse - (int)strlen(text) * 8 / 2, yMouse + 20, text);
	}
}

double Sdl::doubleMin(double x, double y){
	return x < y ? x : y;
}

double Sdl::getDeltaTime(){
	int currentTick = SDL_GetTicks();

	// w tym momencie currentTick - lastTick to czas w milisekundach,
	// jaki uplyna³ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	double deltaTime = (currentTick - lastTick) * 0.001;
	lastTick = currentTick;

	return doubleMin(deltaTime, 0.096);
}

int Sdl::getFps(double deltaTime){
	fpsTimer += deltaTime;
	if(fpsTimer > 0.5){
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};

	frames++;
	return fps;
}