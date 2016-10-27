#pragma once

#include "cocos2d.h"
#include "BaseScoreStrategy.h"
#include "GameLevel.h"
#include "Background.h"
USING_NS_CC;

class MemoryCardScene : public Layer {
public:
	BaseScoreStrategy* scoreStrategy;
	GameLevel* curLevel;
	ScoreData scoreData;
	Background* bg;

	MemoryCardScene();
	virtual ~MemoryCardScene();

	static MemoryCardScene* create(BaseScoreStrategy* strategy);
	static Scene* createScene(BaseScoreStrategy* strategy);
	virtual bool initWithStrategy(BaseScoreStrategy* strategy);
	void newGame();
};