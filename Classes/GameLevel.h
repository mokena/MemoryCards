#pragma once

#include "cocos2d.h"
#include "CardFactory.h"
#include "LevelData.h"
//#include "vector"
#include "Card.h"

USING_NS_CC;

class GameLevel : public CCLayer {
	
	LevelData levelData;
	Vector<Vector<Card*>> cardsTable;

public:
	GameLevel();
	virtual ~GameLevel();

	static GameLevel* create(LevelData data);
	bool initWithData(LevelData data);

protected:
	void initLayout();
};

