#pragma once

#include "platform.hpp"
#include "ladder.hpp"
#include "barrel.hpp"
#include "player.hpp"
#include "hitbox.hpp"
#include "winningArea.hpp"

class Level{
public:
	PlatformArray* platforms;
	LadderArray* ladders;
	BarrelArray* barrels;
	WinningArea* winningArea;
	Player* player;

	// takes ownership of the pointers
	Level(Point playerStartingPoint, PlatformArray* platforms, LadderArray* ladders, BarrelArray* barrels, WinningArea* winningArea);
	~Level();
};

class Levels{
	Level* l1;
	Level* l2;
	Level* l3;
	Level* currentLevel;
	unsigned short lvlID;

	Level* setUpLevel1();
	Level* setUpLevel2();
	Level* setUpLevel3();
	void loadLevelFromFile(Level* destination, char* filename);
public:
	Levels();
	void switchToLevel1();
	void switchToLevel2();
	void switchToLevel3();
	Level* getCurrentLevel();
	void resetCurrentLevel();
};

class LoadLevelFromFile{
	size_t platformArraySize;
	size_t ladderArraySize;
	size_t barrelArraySize;

	Point playerStartingPoint;
	Point barrelSpawnLocation;

	PlatformArray* platforms;
	LadderArray* ladders;
	BarrelArray* barrels;
	WinningArea* winningArea;

	Level* level;
	FILE* fp;
	bool openingSuccesful;
	bool parsingSuccesful;
	bool winningAreaCreated;
	bool platformsCreated;
	bool laddersCreated;
	bool barrelsCreated;
	bool creatingLevelSuccesful;
	bool sizesCorrect;


	void tryToOpenFile(char* filename);

	bool isEof();

	void parseFile();
	void loadSizes();
	void loadPlayerStartingPoint();
	void loadBarrelSpawnLocation();
	void createArrays();
	void loadWinningArea();

	void loadPlatforms();
	void loadPlatform();

	void loadLadders();
	void loadLadder();

	void createLevel();
public:
	LoadLevelFromFile(char* filename);
	~LoadLevelFromFile();

	Level* getLevel();
};