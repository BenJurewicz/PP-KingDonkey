#include "sdl.hpp"

Sdl::Sdl(){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("SDL_Init error: %s\n", SDL_GetError());
		throw "SDL initialization error";
	}

	lastTick = 0;
	fpsTimer = 0;
	frames = 0;
	fps = 0;
	xMouse = 0;
	yMouse = 0;

	createWindowAndRenderer();
	setMiscellaneous();
	createScreen();
	createScreenTexture();
	loadCharset();
	loadGlobalBitMap();
	initColors();
}

void Sdl::createWindowAndRenderer(){
	// tryb pe³noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window,
										 &renderer);

	if(rc != 0){
		SDL_Quit();
		throw sprintf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	};
}

void Sdl::setMiscellaneous(){
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "King Donkey - 198326");

	// wy³¹czenie widocznoœci kursora myszy
	//SDL_ShowCursor(SDL_DISABLE);
}

void Sdl::createScreen(){
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000,
								  0x0000FF00, 0x000000FF, 0xFF000000);
}

void Sdl::createScreenTexture(){
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
							   SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
							   SCREEN_HEIGHT);
}

void Sdl::loadCharset(){
	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL){
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		throw sprintf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
	};
	SDL_SetColorKey(charset, true, 0x000000);
}

void Sdl::loadGlobalBitMap(){
	globalBitMap = SDL_LoadBMP("./Nintendo-64-Donkey-Kong-64-DK-Arcade.bmp");
	if(globalBitMap == NULL){
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		throw sprintf("SDL_LoadBMP(Nintendo-64-Donkey-Kong-64-DK-Arcade.bmp) error: %s\n", SDL_GetError());
	};

	SDL_SetColorKey(globalBitMap, true, 0x000000); // set what color is the alfa channel for transparency
}

void Sdl::initColors(){
	colors.czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors.zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	colors.czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors.niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	colors.jasnyNiebieski = SDL_MapRGB(screen->format, 0x52, 0xB4, 0xFF);
}

Sdl::~Sdl(){
	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(globalBitMap);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}