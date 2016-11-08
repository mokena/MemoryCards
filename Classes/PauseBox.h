#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PauseBox : public Layer {
protected:
	std::function<void()> continueGame;
	std::function<void()> endGame;
public:
	PauseBox();
	virtual ~PauseBox();

	void registerCallback(std::function<void()> continueGame, std::function<void()> endGame);
	virtual bool init();
	CREATE_FUNC(PauseBox);
};
