#include "platform.hpp"

Platform::Platform(int xPos, int yPos, int _lenght) : Entity(42, 66, 841, 864), Point(xPos, yPos){
	width = sprite.width() * _lenght;
	height = sprite.height();

	XSpriteCount = _lenght;
	lenght = _lenght;
}

Platform::Platform() : Platform(0, 0, 0){};

PlatformArray::PlatformArray(size_t _len){
	table = (Platform**)calloc(_len, sizeof(Platform*));
	lenght = _len;
	_i = 0;
}

PlatformArray::~PlatformArray(){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			continue;
		}
		delete table[i];
	}

	free(table);
}

bool PlatformArray::inRange(size_t index){
	return 0 <= index && index < lenght;
}

Platform* PlatformArray::get(size_t index){
	if(inRange(index)){
		return table[index];
	}
	return NULL;
}

void PlatformArray::add(int x, int y, int _lenght){
	if(inRange(_i)){
		table[_i] = new Platform(x, y, _lenght);
		_i++;
	}
}

void PlatformArray::drawAllHitboxes(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawHitbox(table[i]);
	}
}

void PlatformArray::drawAll(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawEntity(*table[i]);
	}
}

size_t PlatformArray::len(){
	return lenght;
}