#include "MemoryCardScene.h"
#include "SceneMediator.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"

MemoryCardScene::MemoryCardScene() :
	scoreData({}),
	curLevel(nullptr),
	pauseBox(nullptr) {
	scoreData.energy = 1000;
}

MemoryCardScene::~MemoryCardScene() {
	unscheduleUpdate();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

Scene* MemoryCardScene::createScene(std::shared_ptr<BaseScoreStrategy> strategy) {
	Scene* scene = Scene::create();
	MemoryCardScene* layer = MemoryCardScene::create(strategy);
	scene->addChild(layer);

	return scene;
}

MemoryCardScene* MemoryCardScene::create(std::shared_ptr<BaseScoreStrategy> strategy) {
	MemoryCardScene* layer = new MemoryCardScene();
	if (layer != nullptr && layer->initWithStrategy(strategy)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool MemoryCardScene::initWithStrategy(std::shared_ptr<BaseScoreStrategy> strategy) {
	scoreStrategy = strategy;
	
	if (Layer::init() == false) {
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("pitpat.mp3");

	initLevelData();
	initUI();

	newGame();

	scheduleUpdate();
	return true;
}

void MemoryCardScene::initLevelData() {
	std::string datas = FileUtils::getInstance()->getStringFromFile("leveldata-1.csv");

	if (datas == "") return;

	std::vector<std::string> rows;

	char* row = strtok((char*)datas.c_str(), "\n");
	while (row) {
		rows.push_back(row);
		row = strtok(nullptr, "\n");
	}

	for (auto row = rows.begin(); row != rows.end(); row++) {
		char* col = strtok((char*)row->c_str(), ",");
		char* ro = strtok(nullptr, ",");
		char* lo = strtok(nullptr, ",");

		if (col == nullptr || ro == nullptr || lo == nullptr) {
			continue;
		}

		LevelData ld = {};
		ld.column = atoi(col);
		ld.row = atoi(ro);
		ld.loss = atoi(lo);

		if (ld.column <= 0 || ld.row <= 0 || (ld.column*ld.row) % 2 != 0 || ld.loss <= 0) {
			continue;
		}

		levelDatas.push_back(ld);
	}
	levelCount = levelDatas.size();
}

void MemoryCardScene::initUI() {
	visibleSize = Director::getInstance()->getVisibleSize();

	bg = Background::create();
	addChild(bg);

	progress = ProgressBar::create();
	progress->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - progress->getContentSize().height / 2 - 20));
	addChild(progress);

	scoreText = ScoreText::create();
	auto scoreSize = scoreText->getContentSize();
	scoreText->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - scoreSize.height / 2 - 20));
	addChild(scoreText);

	pauseBtn = ui::Button::create("pause.png");
	pauseBtn->setAnchorPoint(Vec2(0, 1));
	pauseBtn->setPosition(Vec2(0, visibleSize.height));
	addChild(pauseBtn);

	pauseBtn->addClickEventListener([&](Ref* ref) {
		this->unscheduleUpdate();
		pauseBox = PauseBox::create();
		pauseBox->registerCallback([&]() {
			this->scheduleUpdate();
		}, []() {
			SceneMediator::getInstance()->gotoStartScene();
		});
		this->addChild(pauseBox);
	});
}

void MemoryCardScene::newGame() {
	nowLevel = -1;
	nextLevel();
}

void MemoryCardScene::nextLevel() {
	
	nowLevel++;
	if (nowLevel >= levelCount) {
		nowLevel = 0;
	}
	curData = levelDatas.at(nowLevel);
	auto level = GameLevel::create(curData);
	float scale = visibleSize.width / (level->getContentSize().width + 100);

	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(visibleSize / 2);
	level->setScale(scale);
	if (curLevel != nullptr) {
		curLevel->removeFromParent();
	}
	curLevel = level;
	level->registerCallback([&](CardData* dataA, CardData* dataB) {
		scoreStrategy->execute(&scoreData, dataA, dataB);
		CCLOG("score: %d, energy: %d, max: %d", scoreData.score, scoreData.energy, scoreData.maxContinuous);
		if (dataA->number == dataB->number) {
			CCLOG("paired!");
		}
		else {
			CCLOG("Not a match!");
		}
	}, [this]() {
		nextLevel();
	});

	addChild(curLevel);
}

void MemoryCardScene::update(float dt) {
	Layer::update(dt);

	if (pauseBox != nullptr) {
		pauseBox->removeFromParent();
		pauseBox = nullptr;
	}

	scoreData.energy -= curData.loss*dt;
	if (scoreData.energy > 1000) {
		scoreData.energy = 1000;
	}
	else if (scoreData.energy <= 0) {
		scoreData.energy = 0;

		UserDefault::sharedUserDefault()->setIntegerForKey(NEW_SCORE, scoreData.score);
		//UserDefault::sharedUserDefault()->flush();
		int a = UserDefault::sharedUserDefault()->getIntegerForKey(NEW_SCORE, 0);
		std::vector<int> scoreList;
		scoreList.push_back(scoreData.score);

		for (int i = 0; i < 5; i++) {
			int score = UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
			scoreList.push_back(score);
		}
		std::sort(scoreList.begin(), scoreList.end(), [](int &a, int &b) {
			return a > b;
		});

		int rank = 0;
		for (auto i = scoreList.begin(); i < scoreList.end(); i++) {
			UserDefault::sharedUserDefault()->setIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, rank).c_str(), *i);
			//UserDefault::sharedUserDefault()->flush();
			rank++;
		}
		UserDefault::sharedUserDefault()->flush();
		unscheduleUpdate();
		SceneMediator::getInstance()->gotoChartsScene();
	}

	if (scoreData.energy < 500) {
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((500.0f - scoreData.energy) / 500.0f);
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
	}

	progress->updateView(scoreData.energy);
	scoreText->updateView(scoreData.score);
}

void MemoryCardScene::onExit() {
	Layer::onExit();
	if (pauseBox != nullptr) {
		pauseBox->removeFromParent();
		pauseBox = nullptr;
	}
}