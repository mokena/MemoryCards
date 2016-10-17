#include "Card.h"

Card::Card():
	frontImage(nullptr),
	backImage(nullptr),
	state(CardState::BACK) {
	this->setCascadeColorEnabled(true);
}

Card::~Card() {
	this->removeAllChildren();
}

Node* Card::getFrontImage() {
	return frontImage;
}

Node* Card::getBackImage() {
	return backImage;
}

void Card::setFrontImage(Node* img) {
	if (img == nullptr) return;
	if (img != frontImage && frontImage != nullptr) {
		frontImage->removeFromParent();
	}
	frontImage = img;
	frontImage->setVisible(false);
	frontImage->setCascadeOpacityEnabled(true);
	addChild(frontImage);
}

void Card::setBackImage(Node* img) {
	if (img == nullptr) return;
	if (img != backImage && backImage != nullptr) {
		backImage->removeFromParent();
	}
	backImage = img;
	//backImage->setVisible(false);
	backImage->setCascadeOpacityEnabled(true);
	addChild(backImage);
}

void Card::flipFromTo(Node* a, Node* b, const std::function<void()> &callback) {
	if (a == nullptr || b == nullptr) return;

	//initialize
	a->stopAllActions();
	b->stopAllActions();

	a->setVisible(true);
	a->setScale(1.0f);

	b->setVisible(false);
	b->setScale(0.0f);

	auto flipB = [a, b, callback]() {
		a->setVisible(false);
		b->setVisible(true);
		CallFunc* func = CallFunc::create(callback);
		/*if (callback != nullptr) {
			func = CallFunc::create(callback);
		}*/
		b->runAction(Sequence::create(ScaleTo::create(0.25f, 1.0f, 1.0f), func, NULL));
	};

	a->runAction(
		Sequence::create(ScaleTo::create(0.25f, 0.0f, 1.0f), CallFunc::create(flipB), NULL)
	);
}

void Card::flipToFront(const std::function<void()> &callback) {
	if (state == CardState::FRONT) return;
	flipFromTo(backImage, frontImage, callback);
	state = CardState::FRONT;
}

void Card::flipToBack(const std::function<void()> &callback) {
	if (state == CardState::BACK) return;
	flipFromTo(frontImage, backImage, callback);
	state = CardState::BACK;
}

CardState Card::getCardState() const {
	return state;
}

CardData* Card::getCardData() {
	return &data;
}

void Card::setCardData(CardData data) {
	this->data = data;
}