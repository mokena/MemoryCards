#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ScoreText : public Node {
protected:
	int score;
	ui::TextAtlas *scoreText;

public:
	ScoreText();
	virtual ~ScoreText();

	virtual bool init();
	virtual void updateView(int score);

	CREATE_FUNC(ScoreText);
};
