#include "ChartsScene.h"
#include "UserData.h"
#include "SceneMediator.h"

ChartsScene::ChartsScene() :
	bg(nullptr),
	newScoreImg(nullptr),
	newScore(nullptr),
	chartsImg(nullptr),
	backBtn(nullptr) {
}

ChartsScene::~ChartsScene() {

}

Scene* ChartsScene::createScene() {
	Scene* scene = Scene::create();
	ChartsScene* layer = ChartsScene::create();
	scene->addChild(layer);
	return scene;
}

bool ChartsScene::init() {
	if (Layer::init() == false) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	bg = Background::create();
	addChild(bg);

	backBtn = ui::Button::create("back.png");
	backBtn->setAnchorPoint(Vec2(0, 1));
	backBtn->setPosition(Vec2(10, visibleSize.height - 10));
	addChild(backBtn);
	backBtn->addClickEventListener([](Ref* ref) {
		SceneMediator::getInstance()->gotoStartScene();
	});

	newScoreImg = Sprite::create("new_score.png");
	newScoreImg->setAnchorPoint(Vec2(0, 0.5));
	newScoreImg->setPosition(10, visibleSize.height / 2 + 100);
	addChild(newScoreImg);

	newScore = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	newScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	addChild(newScore);
	int newScr = UserDefault::sharedUserDefault()->getIntegerForKey(NEW_SCORE, 0);
	newScore->setString(StringUtils::format("%d", newScr).c_str());

	chartsImg = Sprite::create("charts_score.png");
	chartsImg->setAnchorPoint(Vec2(0, 0.5));
	chartsImg->setPosition(Vec2(10, visibleSize.height / 2));
	addChild(chartsImg);

	for (int i = 0; i < 5; i++) {
		int score = UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format(
			"%s%d", RANK_SCORE, i).c_str(), 0);
		Node* chartRow = createChartRow(i, score);
		addChild(chartRow);
	}

	return true;
}

Node* ChartsScene::createChartRow(int rank, int score) {
	auto size = Director::getInstance()->getVisibleSize();
	Node* row = Node::create();
	ui::TextAtlas* rankTitle = ui::TextAtlas::create(StringUtils::format("%d", rank+1).c_str(), "number.png",
		63, 83, "0");
	rankTitle->setAnchorPoint(Vec2(0, 1));
	rankTitle->setPosition(Vec2(10, size.height / 2 - (rank + 1) * 50));
	row->addChild(rankTitle);

	ui::TextAtlas* rankScore = ui::TextAtlas::create(StringUtils::format("%d", score).c_str(), "number.png",
		63, 83, "0");
	rankScore->setAnchorPoint(Vec2(1, 1));
	rankScore->setPosition(Vec2(size.width - 10, size.height / 2 - (rank + 1) * 50));
	row->addChild(rankScore);

	row->setContentSize(Size(size.width, 70));
	return row;

}