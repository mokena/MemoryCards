#pragma once

#include "cocos2d.h"

USING_NS_CC;

class SceneMediator {
protected:
	static SceneMediator* instance;
public:
	static SceneMediator* getInstance();
	void gotoGameScene();
	void gotoStartScene();
	void gotoChartsScene();
};
