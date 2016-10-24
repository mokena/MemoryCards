#include "MemoryCardScene.h"

MemoryCardScene::MemoryCardScene() :
	scoreData({}),
	curLevel(nullptr) {
}

MemoryCardScene::~MemoryCardScene() {

}

Scene* MemoryCardScene::createScene(BaseScoreStrategy* strategy) {
	Scene* scene = Scene::create();
	MemoryCardScene* layer = MemoryCardScene::create(strategy);
	scene->addChild(layer);

	return scene;
}

MemoryCardScene* MemoryCardScene::create(BaseScoreStrategy* strategy) {
	MemoryCardScene* layer = new MemoryCardScene();
	if (layer != nullptr && layer->initWithStrategy(strategy)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}


bool MemoryCardScene::initWithStrategy(BaseScoreStrategy* strategy) {
	scoreStrategy = strategy;
	if (Layer::init() == false) {
		return false;
	}

	newGame();
	return true;
}
void MemoryCardScene::newGame() {

	scoreData.energy = 1000;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	LevelData data = {};
	data.column = 4;
	data.row = 4;
	auto level = GameLevel::create(data);
	float scale = visibleSize.width / (level->getContentSize().width + 40);

	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(visibleSize / 2);
	level->setScale(scale);
	level->registerCallback([&](CardData* dataA, CardData* dataB) {
		scoreStrategy->execute(&scoreData, dataA, dataB);
		CCLOG("score: %d, energy: %d, max: %d", scoreData.score, scoreData.energy, scoreData.maxContinuous);
		if (dataA->number == dataB->number) {
			CCLOG("paired!");
		}
		else {
			CCLOG("Not a match!");
		}
	}, [&]() {
		CCLOG("Congratulations, you finished!");
	});

	addChild(level);
}