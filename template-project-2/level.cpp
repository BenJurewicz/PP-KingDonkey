#include "level.hpp"

Level::Level(Point playerStartingPoint, PlatformArray* _platforms, LadderArray* _ladders, BarrelArray* _barrels, WinningArea* _winningArea){
	player = new Player(playerStartingPoint.x, playerStartingPoint.y);
	platforms = _platforms;
	ladders = _ladders;
	barrels = _barrels;
	winningArea = _winningArea;
}

Level::~Level(){
	delete player;
	delete platforms;
	delete ladders;
	delete barrels;
	delete winningArea;
}

Levels::Levels() : l1(Levels::setUpLevel1()), l2(Levels::setUpLevel2()), l3(Levels::setUpLevel3()){
	currentLevel = l1;
	lvlID = 1;
}

Level* Levels::setUpLevel1(){
	LoadLevelFromFile loadLevelFromFile("Level1.txt");
	Level* level = loadLevelFromFile.getLevel();
	return level;
}
Level* Levels::setUpLevel2(){
	LoadLevelFromFile loadLevelFromFile("Level2.txt");
	Level* level = loadLevelFromFile.getLevel();
	return level;
}
Level* Levels::setUpLevel3(){
	LoadLevelFromFile loadLevelFromFile("Level3.txt");
	Level* level = loadLevelFromFile.getLevel();
	return level;
}

void Levels::switchToLevel1(){
	resetCurrentLevel();
	currentLevel = l1;
	lvlID = 1;
}

void Levels::switchToLevel2(){
	resetCurrentLevel();
	currentLevel = l2;
	lvlID = 2;
	resetCurrentLevel();
}

void Levels::switchToLevel3(){
	resetCurrentLevel();
	currentLevel = l3;
	lvlID = 3;
}

Level* Levels::getCurrentLevel(){
	return currentLevel;
}

void Levels::resetCurrentLevel(){
	switch(lvlID){
		case 1:
			delete l1;
			l1 = setUpLevel1();
			currentLevel = l1;
			break;
		case 2:
			delete l2;
			l2 = setUpLevel2();
			currentLevel = l2;
			break;
		case 3:
			delete l3;
			l3 = setUpLevel3();
			currentLevel = l3;
			break;

	}
}

LoadLevelFromFile::LoadLevelFromFile(char* filename){
	openingSuccesful = false;
	parsingSuccesful = false;
	winningAreaCreated = false;
	platformsCreated = false;
	laddersCreated = false;
	barrelsCreated = false;
	sizesCorrect = true;

	platformArraySize = 0;
	ladderArraySize = 0;
	barrelArraySize = 0;

	tryToOpenFile(filename);
	parseFile();
	if(sizesCorrect == false){
		creatingLevelSuccesful = false;
		printf("Wrong data in level file \n\n");
		exit(0);
		return;
	}

	createLevel();
}

LoadLevelFromFile::~LoadLevelFromFile(){
	fclose(fp);
	if(creatingLevelSuccesful){
		return;
	}
	// creating level failed from here
	if(winningAreaCreated){
		delete winningArea;
	}
	if(platformsCreated){
		delete platforms;
	}
	if(laddersCreated){
		delete ladders;
	}
	if(barrelsCreated){
		delete barrels;
	}
}

void LoadLevelFromFile::parseFile(){
	loadSizes();
	loadPlayerStartingPoint();
	loadBarrelSpawnLocation();
	createArrays();
	loadWinningArea();
	loadPlatforms();
	loadLadders();
	if(sizesCorrect == false){
		return;
	}

	parsingSuccesful = true;
}

void LoadLevelFromFile::loadSizes(){
	fscanf_s(fp, "PlatformArraySize %d\n", &platformArraySize);
	fscanf(fp, "LadderArraySize %d\n", &ladderArraySize);
	fscanf(fp, "BarrelArraySize %d\n", &barrelArraySize);
	fscanf(fp, "\n");
}

void LoadLevelFromFile::loadPlayerStartingPoint(){
	//PlayerStartingLocation 900 677
	int x, y;
	fscanf(fp, "PlayerStartingLocation %d %d\n", &x, &y);
	playerStartingPoint = Point(x, y);
}

void LoadLevelFromFile::loadBarrelSpawnLocation(){
	//BarrelSpawnLocation 450 100
	int x, y;
	fscanf(fp, "BarrelSpawnLocation %d %d\n", &x, &y);
	barrelSpawnLocation = Point(x, y);
}

void LoadLevelFromFile::createArrays(){
	platforms = new PlatformArray(platformArraySize);
	platformsCreated = true;

	ladders = new LadderArray(ladderArraySize);
	laddersCreated = true;

	barrels = new BarrelArray(barrelArraySize, barrelSpawnLocation.x, barrelSpawnLocation.y);
	barrelsCreated = true;
}

void LoadLevelFromFile::loadWinningArea(){
	//WinningArea 250 50 500 100
	int x, y, width, height;
	fscanf(fp, "WinningArea %d %d %d %d\n", &x, &y, &width, &height);
	winningArea = new WinningArea(x, y, width, height);
	winningAreaCreated = true;
	fscanf(fp, "\n");
}

void LoadLevelFromFile::loadPlatforms(){
	if(sizesCorrect == false){
		return;
	}
	for(int i = 0; i < platformArraySize; i++){
		if(isEof()){
			sizesCorrect = false;
			break;
		} else{
			loadPlatform();
		}
	}
	fscanf(fp, "\n");
}

void LoadLevelFromFile::loadPlatform(){
	//Platform 0 727 42
	int x, y, lenghtInSpriteWidth;
	char table[50];
	fgets(table, 49, fp);
	int succesfulyFilledCount = sscanf_s(table, "Platform %d %d %d\n", &x, &y, &lenghtInSpriteWidth);
	if(succesfulyFilledCount < 3){
		return;
	}
	platforms->add(x, y, lenghtInSpriteWidth);
}

void LoadLevelFromFile::loadLadders(){
	if(sizesCorrect == false){
		return;
	}

	for(int i = 0; i < ladderArraySize; i++){
		if(isEof()){
			sizesCorrect = false;
			break;
		}
		loadLadder();
	}
}

void LoadLevelFromFile::loadLadder(){
	//Ladder 500 619 9
	int x, y, lenghtInSpriteHeight;
	char table[50];

	fgets(table, 49, fp);
	int succesfulyFilledCount = sscanf_s(table, "Ladder %d %d %d\n", &x, &y, &lenghtInSpriteHeight);
	if(succesfulyFilledCount < 3){
		sizesCorrect = false;
		return;
	}

	ladders->add(x, y, lenghtInSpriteHeight);
}

void LoadLevelFromFile::createLevel(){
	if(parsingSuccesful == false){
		return;
	}
	level = new Level(playerStartingPoint, platforms, ladders, barrels, winningArea);
	creatingLevelSuccesful = true;
}

bool LoadLevelFromFile::isEof(){
	return feof(fp) != 0;
}

Level* LoadLevelFromFile::getLevel(){
	if(creatingLevelSuccesful){
		return level;
	} else{
		return NULL;
	}
}

void LoadLevelFromFile::tryToOpenFile(char* filename){
	fp = fopen(filename, "r");
	if(fp == NULL){
		openingSuccesful = true;
	}
}