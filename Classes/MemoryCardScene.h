#pragma once

#include "cocos2d.h"
#include "BaseScoreStrategy.h"
#include "GameLevel.h"
#include "Background.h"
#include "ProgressBar.h"
#include "ScoreText.h"
#include "PauseBox.h"
USING_NS_CC;

class MemoryCardScene : public Layer {
public:
	std::shared_ptr<BaseScoreStrategy> scoreStrategy;
	GameLevel* curLevel;
	ScoreData scoreData;
	Background* bg;
	ProgressBar* progress;
	ScoreText* scoreText;
	Size visibleSize;
	LevelData curData;
	ui::Button* pauseBtn;
	PauseBox* pauseBox;

	int nowLevel;
	int levelCount;
	std::vector<LevelData> levelDatas;

	MemoryCardScene();
	virtual ~MemoryCardScene();

	static MemoryCardScene* create(std::shared_ptr<BaseScoreStrategy> strategy);
	static Scene* createScene(std::shared_ptr<BaseScoreStrategy> strategy);
	virtual bool initWithStrategy(std::shared_ptr<BaseScoreStrategy> strategy);
	void newGame();
	void update(float dt);

	void nextLevel();
	void initLevelData();
	void initUI();
	virtual void onExit();
};