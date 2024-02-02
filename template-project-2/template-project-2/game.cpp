#include "game.hpp"

Game::Game(){
	quit = 0;

	worldTime = 0;
	delta;
	mouseMoved = false;
	barrelPlayerCollision = false;
	startNewGame = false;
	isInWinningArea = false;
}

void Game::programLoop(){
	while(!quit){
		worldTime = 0;
		delta = 0;
		mouseMoved = false;
		barrelPlayerCollision = false;
		startNewGame = false;
		isInWinningArea = false;

		level = levels.getCurrentLevel();
		platforms = level->platforms;
		ladders = level->ladders;
		barrels = level->barrels;
		winningArea = level->winningArea;
		player = level->player;

		gameLoop();
	}
}

void Game::gameLoop(){
	while(!quit && !startNewGame){
		//Sleep(20);
		//Sleep(100);
		delta = sdl.getDeltaTime();
		worldTime += delta;

		sdl.clearScreen();

		sdl.drawHitbox(winningArea);

		//platforms->drawAllHitboxes(sdl);
		platforms->drawAll(sdl);

		//ladders->drawAllHitboxes(sdl);
		ladders->drawAll(sdl);

		barrels->spawnNew(worldTime);
		barrels->updateAll(delta, worldTime, *platforms);
		//barrels->drawAllHitboxes(sdl);
		barrels->drawAll(sdl);

		player->update(delta, worldTime, *platforms, *ladders, *barrels, barrelPlayerCollision);

		isInWinningArea = player->isColliding(winningArea);

		//sdl.drawHitbox(&player);
		sdl.drawEntity(*player);

		drawInformationRectangle();

		sdl.refreshScreen();

		handeInput();
	}
}

void Game::drawInformationRectangle(){
	// tekst informacyjny
	sdl.drawRectangle(4, 4, SCREEN_WIDTH - 8, 36, sdl.colors.czerwony, sdl.colors.niebieski);
	drawSaticText(sdl.getFps(delta));
	printBarrelAndWinningAreaCollsion();
	sdl.printMouseCords(sdl, mouseMoved);
}

void Game::printBarrelAndWinningAreaCollsion(){
	char text[50];
	sprintf(text, "barrelPlayerCollision = %d", barrelPlayerCollision);
	sdl.drawString(10, 10, text);

	sprintf(text, "playerInWinningArea = %d", isInWinningArea);
	sdl.drawString(10, 24, text);
}

void Game::drawSaticText(double fps){
	char text[128];

	sprintf_s(
		text,
		"Czas trwania = %.1lf s  %.0lf klatek / s",
		worldTime, fps);
	sdl.drawString(sdl.getScreenWidth() / 2 - (int)strlen(text) * 8 / 2, 10, text);

	//sprintf_s(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
	//sdl.drawString(sdl.getScreenWidth() / 2 - (int)strlen(text) * 8 / 2, 26, text);
	sprintf_s(text, "Wykonane podpunkty: Obowiazkowe, A, B, C, E(gracz i beczki), I");
	sdl.drawString(sdl.getScreenWidth() / 2 - (int)strlen(text) * 8 / 2, 26, text);
}

void Game::handeInput(){
	// obs³uga zdarzeñ (o ile jakieœ zasz³y)
	while(SDL_PollEvent(&event)){
		if(PRINT_CURSOR_CORDS && event.type == SDL_MOUSEMOTION){
			mouseMoved = true;
		}

		switch(event.type){
			case SDL_KEYDOWN:
				handleKeyPressed();
				break;
			case SDL_KEYUP:
				handleKeyLetGo();
				break;
			case SDL_QUIT:
				quit = 1;
				break;
		};
	};
}

void Game::handleKeyPressed(){
	if(event.key.keysym.sym == SDLK_ESCAPE){
		quit = 1;
	} else if(event.key.keysym.sym == SDLK_UP){
		player->wantsToClimbUp();
	} else if(event.key.keysym.sym == SDLK_DOWN){
		player->wantsToClimbDown();
	} else if(event.key.keysym.sym == SDLK_LEFT){
		player->moveLeft();
	} else if(event.key.keysym.sym == SDLK_RIGHT){
		player->moveRight();
	} else if(event.key.keysym.sym == SDLK_SPACE){
		player->jump();
	} else if(event.key.keysym.sym == SDLK_n){
		startNewGame = true;
		levels.resetCurrentLevel();
	} else if(event.key.keysym.sym == SDLK_1){
		levels.switchToLevel1();
		startNewGame = true;
	} else if(event.key.keysym.sym == SDLK_2){
		levels.switchToLevel2();
		startNewGame = true;
	} else if(event.key.keysym.sym == SDLK_3){
		levels.switchToLevel3();
		startNewGame = true;
	}
}

void Game::handleKeyLetGo(){
	if(event.key.keysym.sym == SDLK_UP){
		player->stopClimbing();
	} else if(event.key.keysym.sym == SDLK_DOWN){
		player->stopClimbing();
	} else if(event.key.keysym.sym == SDLK_LEFT){
		player->stopX();
	} else if(event.key.keysym.sym == SDLK_RIGHT){
		player->stopX();
	}
}