#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Background.h"

USING_NS_CC;

class ChartsScene : public Layer {
protected:
	Background* bg;
	Sprite* newScoreImg;
	ui::TextAtlas* newScore;
	Sprite* chartsImg;
	std::vector<Node*> chartList;
	ui::Button* backBtn;

	Node* createChartRow(int rank, int score);

public:
	ChartsScene();
	virtual ~ChartsScene();

	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(ChartsScene);
};
