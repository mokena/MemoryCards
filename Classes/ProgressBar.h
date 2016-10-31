#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ProgressBar : public Node {
protected:
	float percentage;
	ProgressTimer* progress;
	Sprite* bg;
public:
	ProgressBar();

	virtual bool init();
	virtual void updateView(int energy);
	CREATE_FUNC(ProgressBar);
};