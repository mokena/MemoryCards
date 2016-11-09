#pragma once
#include "cocos2d.h"
#include "Background.h"
#include "ui/CocosGUI.h"
#include "ScoreStrategy.h"
#include "MemoryCardScene.h"

USING_NS_CC;

class StartScene : public Layer {
public:
	Background* bg;
	Sprite* logo;
	ui::Button* startBtn;
	ui::Button* chartBtn;
	ui::Button* exitBtn;

	StartScene();
	virtual ~StartScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
};
