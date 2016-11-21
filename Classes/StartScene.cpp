#include "StartScene.h"
#include "SceneMediator.h"

StartScene::StartScene() :
	bg(nullptr),
	logo(nullptr),
	startBtn(nullptr),
	chartBtn(nullptr),
	exitBtn(nullptr) {

}

StartScene::~StartScene() {

}

Scene* StartScene::createScene() {
	Scene* scene = Scene::create();
	StartScene* layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init() {
	if (Layer::init() == false) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	bg = Background::create();
	addChild(bg);

	logo = Sprite::create("logo.png");
	logo->setAnchorPoint(Vec2(1, 1));
	logo->setPosition(visibleSize.width, visibleSize.height);
	addChild(logo);

	startBtn = ui::Button::create("start.png");
	startBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	addChild(startBtn);
	startBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoGameScene();
	});

	chartBtn = ui::Button::create("charts.png");
	chartBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 110));
	addChild(chartBtn);
	chartBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoChartsScene();
	});

	exitBtn = ui::Button::create("exit.png");
	exitBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 170));
	addChild(exitBtn);
	return true;
}
