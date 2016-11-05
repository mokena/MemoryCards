#include "GameLevel.h"

GameLevel::GameLevel() :
selectedA(nullptr),
selectedB(nullptr),
pairCallback(nullptr),
completeCallback(nullptr) {
}

GameLevel::~GameLevel() {
	removeAllChildren();
}

GameLevel* GameLevel::create(LevelData data) {
	GameLevel* level = new GameLevel();
	if (level && level->initWithData(data)) {
		level->autorelease();
		return level;
	}
	CC_SAFE_DELETE(level);
	return nullptr;
}

bool GameLevel::initWithData(LevelData data) {
	levelData = data;
	if (!CCLayer::init()) {
		return false;
	}

	if (data.column*data.row % 2 != 0) {
		return false;
	}

	levelData = data;
	
	initLayout();
	initTouchEvent();
	return true;
}

void GameLevel::initLayout() {
	for (int i = 0; i < levelData.column; i++) {
		std::vector<Card*> r(levelData.row);
		cardsTable.push_back(r);
	}
	
	srand(time(nullptr));

	int bgColor = floor(CCRANDOM_0_1() * 8);
	CardFactory factory;
	int number = 0, space = 40;
	Vector<Card*> initCards;
	for (number = 0; number < levelData.column*levelData.row; number++) {
		Card* card = (Card*)(factory.createCard(bgColor, number / 2));
		initCards.pushBack(card);
	}
	remainCards = levelData.column*levelData.row;

	for (int column = 0; column < levelData.column; column++) {
		for (int row = 0; row < levelData.row; row++) {
			Card* card = initCards.at(CCRANDOM_0_1()*initCards.size());
			initCards.eraseObject(card);
			card->getCardData()->column = column;
			card->getCardData()->row = row;
			Size cardSize = card->getContentSize();
			card->setPosition(Vec2((cardSize.width + space)*row + cardSize.width / 2,
				(cardSize.height + space)*column + cardSize.height / 2));
			cardsTable[column][row] = card;
			this->addChild(card);

			if (column == levelData.column - 1 && row == levelData.row - 1) {

				this->setContentSize(Size((cardSize.width + space)*(levelData.row - 1) + cardSize.width,
					(cardSize.height + space)*(levelData.column - 1) + cardSize.height));
			}
		}
	}

}

void GameLevel::initTouchEvent() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t, Event* e) {
		//whether the level area is touched
		Point pos = this->convertToNodeSpace(t->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(pos)) {
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [&](Touch* t, Event* e) {
		Point pos = this->convertToNodeSpace(t->getLocation());
		Card* selCard = nullptr;

		for (int i = 0; i < levelData.column; i++) {
			auto cards = cardsTable[i];
			if (selCard) break;
			for (int j = 0; j < levelData.row; j++) {
				Card* card = cards[j];
				if (!card) continue;
				auto size = card->getContentSize();
				auto ps = card->getPosition();
				Rect rect = Rect(ps.x - size.width/2, ps.y - size.height/2, 
					card->getContentSize().width, card->getContentSize().height);
				if (rect.containsPoint(pos)) {
					selCard = card;
					break;
				}
			}
		}

		if (selCard == nullptr || selCard == selectedA) {
			return;
		}

		if (selectedA == nullptr) {
			selectedA = selCard;
			selectedA->flipToFront();
		}
		else {
			selectedB = selCard;
			Card* sa = selectedA;
			Card* sb = selectedB;
			CardData* dataA = sa->getCardData();
			CardData* dataB = sb->getCardData();
			if (pairCallback != nullptr) {
				pairCallback(dataA, dataB);
			}

			if (dataA->number == dataB->number) {
				selectedB->flipToFront([&, sa, sb]() {
					//sa->runAction(Spawn::create();
					sa->removeFromParent();
					sb->removeFromParent();
				});
				cardsTable[dataA->column][dataA->row] = nullptr;
				cardsTable[dataB->column][dataB->row] = nullptr;
				remainCards -= 2;
				CCLOG("remainCards: %d", remainCards);
				if (remainCards == 0 && completeCallback != nullptr) {
					completeCallback();
				}
			}
			else {
				selectedB->flipToFront([&, sa, sb]() {
					sa->flipToBack();
					sb->flipToBack();
				});
			}
			selectedA = nullptr;
			selectedB = nullptr;
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLevel::registerCallback(std::function<void(CardData*, CardData*)> pairFunc, std::function<void()> completeFunc) {
	pairCallback = pairFunc;
	completeCallback = completeFunc;
}