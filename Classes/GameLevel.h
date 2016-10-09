#pragma once

#include "cocos2d.h"
#include "CardFactory.h"
#include "LevelData.h"
#include <vector>
#include "Card.h"

USING_NS_CC;

class GameLevel : public Layer {
	
	LevelData levelData;
	std::vector<std::vector<Card*>> cardsTable;
	int remainCards;//how many cards remains

public:
	GameLevel();
	virtual ~GameLevel();

	static GameLevel* create(LevelData data);
	bool initWithData(LevelData data);

protected:
	void initLayout();
};

