#include "MemoryCardScene.h"

MemoryCardScene::MemoryCardScene() :
	scoreData({}),
	curLevel(nullptr) {
}

MemoryCardScene::~MemoryCardScene() {
	unscheduleUpdate();
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

	visibleSize = Director::getInstance()->getVisibleSize();

	bg = Background::create();
	addChild(bg);

	progress = ProgressBar::create();
	progress->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - progress->getContentSize().height/2 - 20));
	addChild(progress);

	scoreText = ScoreText::create();
	auto scoreSize = scoreText->getContentSize();
	scoreText->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - scoreSize.height/2 - 20));
	addChild(scoreText);

	newGame();

	scheduleUpdate();
	return true;
}
void MemoryCardScene::newGame() {

	scoreData.energy = 1000;
	
	LevelData data = {};
	data.column = 4;
	data.row = 4;
	data.loss = 20;
	curData = data;
	auto level = curLevel = GameLevel::create(data);
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

void MemoryCardScene::update(float dt) {
	Layer::update(dt);
	scoreData.energy -= curData.loss*dt;
	if (scoreData.energy > 1000) {
		scoreData.energy = 1000;
	}
	else if (scoreData.energy < 0) {
		scoreData.energy = 0;
	}

	progress->updateView(scoreData.energy);
	scoreText->updateView(scoreData.score);
}