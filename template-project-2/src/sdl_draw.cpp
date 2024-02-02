#include "sdl.hpp"

int Sdl::getScreenWidth(){
	return screen->w;
}

int Sdl::getScreenHeight(){
	return screen->h;
}

void Sdl::drawString(int x, int y, const char* text){
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text){
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
}

void Sdl::drawSurface(SDL_Surface* sprite, int x, int y){
	SDL_Rect dest;
	// this draws the surface in the middle of the coordinates
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

void Sdl::drawPixel(int x, int y, Uint32 color){
	int bpp = screen->format->BytesPerPixel;
	Uint8* p = (Uint8*)screen->pixels + y * screen->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Sdl::drawLine(int x, int y, int l, int dx, int dy,
				   Uint32 color){
	for(int i = 0; i < l; i++){
		drawPixel(x, y, color);
		x += dx;
		y += dy;
	};
};

void Sdl::drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor){
	int i;
	drawLine(x, y, k, 0, 1, outlineColor);
	drawLine(x + l - 1, y, k, 0, 1, outlineColor);
	drawLine(x, y, l, 1, 0, outlineColor);
	drawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++){
		drawLine(x + 1, i, l - 2, 1, 0, fillColor);
	}
};

void Sdl::drawEntity(Entity entity){
	int sWidth = entity.sprite.width();
	int sHeight = entity.sprite.height();

	SDL_Rect dest;
	setRectValues(dest, entity.x, entity.y, globalBitMap->w, globalBitMap->w);

	SDL_Rect mask;
	setRectValues(mask, entity.sprite.xLeft, entity.sprite.yUp, sWidth, sHeight);

	for(int i = entity.XSpriteCount; i > 0; i--){
		for(int j = entity.YSpriteCount; j > 0; j--){
			SDL_BlitSurface(globalBitMap, &mask, screen, &dest);
			moveDest(dest, sWidth, sHeight, 0, (j > 1));
		}
		dest.y = entity.y;
		moveDest(dest, sWidth, sHeight, (i > 1), 0);
	}
}

void Sdl::setRectValues(SDL_Rect& mask, int xPos, int yPos, int width, int height){
	mask.x = xPos;
	mask.y = yPos;

	mask.w = width;
	mask.h = height;
}

void Sdl::moveDest(SDL_Rect& dest, int entityWidth, int entityHeight, int xMove, int yMove){
	dest.x += entityWidth * xMove;
	dest.y += entityHeight * yMove;
}

void Sdl::drawHitbox(Hitbox* hitbox){
	//if(RectangleHitbox* rect = dynamic_cast<RectangleHitbox*>(hitbox)){
	//	drawHitbox(rect);
	//} else if(CircleHitbox* circle = dynamic_cast<CircleHitbox*>(hitbox)){
	//	drawHitbox(circle);
	//} else{
	//	printf_s("Problems in Sdl::drwaHitbox()");
	//}
}

void Sdl::drawHitbox(RectangleHitbox* hitbox){
	drawRectangle(hitbox->x, hitbox->y, hitbox->width, hitbox->height, colors.niebieski, colors.jasnyNiebieski);
}

void Sdl::drawHitbox(CircleHitbox* hitbox){
	//printf_s("Sdl::drawHitbox(CircleHitbox* hitbox not implemented\n");

	int xLeftPos = hitbox->x;
	int xRightPos = hitbox->x + 2*hitbox->radius;

	int yUpPos = hitbox->y;
	int yDownPos = hitbox->y + 2*hitbox->radius;

	double distanceFrormCenter;
	for(int x = xLeftPos; x < xRightPos; x++){
		for(int y = yUpPos; y < yDownPos; y++){
			distanceFrormCenter = hitbox->getDistanceFromCenter(x, y);
			//printf("dFCenter = %d; r = %d; bool = %d; x = %d, y = %d, centX = %d, centY = %d \n",
			//	   distanceFrormCenter, hitbox->radius, distanceFrormCenter < hitbox->radius, x, y, hitbox->getCenterX(), hitbox->getCenterY());
			if(distanceFrormCenter < hitbox->radius && x%6!=0 && y%6!=0){
				drawPixel(x, y, colors.jasnyNiebieski);
			}
		}
	}
}

void Sdl::refreshScreen(){
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//SDL_RenderClear(renderer); // clears the whole screen
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Sdl::clearScreen(){
	SDL_FillRect(screen, NULL, colors.czarny);
	//SDL_FillRect(screen, NULL, colors.zielony);
}