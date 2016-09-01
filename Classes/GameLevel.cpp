#include "GameLevel.h"

GameLevel::GameLevel() {}

GameLevel::~GameLevel() {
	removeAllChildren();
}

GameLevel* GameLevel::create(LevelData data) {
	GameLevel* level = new GameLevel();
	if (level && level->initWithData(data)) {
		level->autorelease();
		return level;
	}
	CC_SAFE_DELETE(level);
	return nullptr;
}

bool GameLevel::initWithData(LevelData data) {
	levelData = data;
	if (!CCLayer::init()) {
		return false;
	}



	return true;
}

