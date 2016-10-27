#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Background : public Node {
protected:
	Sprite* bg;
public:
	Background();
	virtual ~Background();

	CREATE_FUNC(Background);

	virtual bool init();
	virtual void update(float dt);
};
