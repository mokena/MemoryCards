#include "SceneMediator.h"
#include "ScoreStrategy.h"
#include "MemoryCardScene.h"
#include "StartScene.h"
#include "ChartsScene.h"

void SceneMediator::gotoGameScene() {
	std::shared_ptr<ScoreStrategy> strategy(new ScoreStrategy());
	auto scene = MemoryCardScene::createScene(strategy);
	Director::getInstance()->replaceScene(scene);
}

void SceneMediator::gotoStartScene() {
	Scene* scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SceneMediator::gotoChartsScene() {
	Scene* scene = ChartsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}