#include "ScoreText.h"

ScoreText::ScoreText() :
	score(0) {

}

ScoreText::~ScoreText() {}

bool ScoreText::init() {
	if (Node::init() == false) {
		return false;
	}

	scoreText = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	scoreText->setAnchorPoint(Vec2(1, 0.5f));
	addChild(scoreText);

	return true;
}

void ScoreText::updateView(int score) {
	if (score != this->score) {
		this->score = score;
		scoreText->setString(StringUtils::format("%d", score));

		auto effect = scoreText->clone();
		effect->runAction(Sequence::create(Spawn::create(
			ScaleTo::create(0.25f, 2), FadeOut::create(0.25f), NULL), CallFunc::create([effect]() {
			effect->removeFromParent();
		}), NULL));
		addChild(effect);
	}
}