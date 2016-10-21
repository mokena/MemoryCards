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

	Card* selectedA;
	Card* selectedB;

	std::function<void(CardData*, CardData*)> pairCallback;
	std::function<void()> completeCallback;

public:
	GameLevel();
	virtual ~GameLevel();

	static GameLevel* create(LevelData data);
	bool initWithData(LevelData data);
	void initTouchEvent();

	void registerCallback(std::function<void(CardData*, CardData*)> pairFunc, std::function<void()> completeFunc);

protected:
	void initLayout();
};

