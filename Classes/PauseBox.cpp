#include "PauseBox.h"
#include "ui/CocosGUI.h"

PauseBox::PauseBox() :
	continueGame(nullptr),
	endGame(nullptr) {

}

PauseBox::~PauseBox() {

}

bool PauseBox::init() {
	if (Layer::init() == false) {
		return false;
	}

	auto viewSize = Director::getInstance()->getVisibleSize();

	auto background = LayerColor::create(Color4B(0, 0, 0, 200));
	auto box = ui::Scale9Sprite::create("message_box.png");
	auto continueBtn = ui::Button::create("continue.png");
	auto endBtn = ui::Button::create("end_game.png");

	box->setContentSize(Size(450, 450));
	box->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));
	continueBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 70));
	endBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 70));

	continueBtn->addClickEventListener([this](Ref* ref) {
		if (continueGame != nullptr) {
			continueGame();
		}
	});
	endBtn->addClickEventListener([this](Ref* ref) {
		if (endGame != nullptr) {
			endGame();
		}
	});
	
	setContentSize(viewSize);
	addChild(background);
	addChild(box);
	addChild(continueBtn);
	addChild(endBtn);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* t, Event* e) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void PauseBox::registerCallback(std::function<void()> continueGame, std::function<void()> endGame) {
	this->continueGame = continueGame;
	this->endGame = endGame;
}