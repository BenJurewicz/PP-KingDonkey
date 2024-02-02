#include "ladder.hpp"

Ladder::Ladder(int xPos, int yPos, int _lenght) : Point(xPos, yPos), Entity(81, 105, 852, 864){
	width = sprite.width();
	height = sprite.height() * _lenght;

	YSpriteCount = _lenght;
	lenght = _lenght;
}

Ladder::Ladder() : Ladder(0, 0, 0){};

LadderArray::LadderArray(size_t _len){
	table = (Ladder**)calloc(_len, sizeof(Ladder*));
	lenght = _len;
	_i = 0;
}

LadderArray::~LadderArray(){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			continue;
		}
		delete table[i];
	}

	free(table);
}

size_t LadderArray::len(){
	return lenght;
}

bool LadderArray::inRange(size_t index){
	return 0 <= index && index < lenght;
}

Ladder* LadderArray::get(size_t index){
	if(inRange(index)){
		return table[index];
	}
	return NULL;
}

void LadderArray::add(int x, int y, int _lenght){
	if(inRange(_i)){
		table[_i] = new Ladder(x, y, _lenght);
		_i++;
	}
}

void  LadderArray::drawAllHitboxes(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawHitbox(table[i]);
	}
}

void  LadderArray::drawAll(Sdl& sdl){
	for(size_t i = 0; i < lenght; i++){
		if(table[i] == NULL){
			break;
		}
		sdl.drawEntity(*table[i]);
	}
}