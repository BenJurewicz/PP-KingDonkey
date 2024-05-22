#include "game.hpp"

// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv){
	srand((unsigned int)time(NULL));
	Game game;
	game.programLoop();
	return 0;
};