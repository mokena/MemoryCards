#include "Background.h"

Background::Background() {}

Background::~Background() {
	unscheduleUpdate();
}

bool Background::init() {
	if (Node::init() == false) {
		return false;
	}

	bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vect(0, 0));

	Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	bg->getTexture()->setTexParameters(tp);
	
	Size viewSize = Director::getInstance()->getVisibleSize();
	Rect rect = Rect(0, 0, viewSize.width, viewSize.height);
	bg->setTextureRect(rect);

	addChild(bg);

	scheduleUpdate();
	return true;
}

void Background::update(float dt) {
	Node::update(dt);

	Rect rect = bg->getTextureRect();
	rect.origin.x += 100.0f*dt;
	rect.origin.y += 100.0f*dt;
	bg->setTextureRect(rect);
}