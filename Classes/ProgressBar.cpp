#include "ProgressBar.h"

ProgressBar::ProgressBar() :
percentage(0.0f){

}

bool ProgressBar::init() {
	if (Node::init() == false) {
		return false;
	}

	bg = Sprite::create("energy_back.png");
	addChild(bg);

	progress = ProgressTimer::create(Sprite::create("energy_front.png"));
	progress->setType(ProgressTimer::Type::BAR);
	progress->setMidpoint(Vec2(0, 0));
	progress->setBarChangeRate(Vec2(1, 0));
	
	progress->setPercentage(100.0f);
	addChild(progress);

	setContentSize(bg->getContentSize());
	return true;
}

void ProgressBar::updateView(int energy) {
	float per = energy / 1000.0f*100;
	
	if (abs(per - percentage) > 1.0f) {
		progress->runAction(EaseBackOut::create(ProgressTo::create(0.25f, per)));
		percentage = per;
	}
	
	//progress->setPercentage(percentage);	
}