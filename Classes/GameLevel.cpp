#include "GameLevel.h"

GameLevel::GameLevel() {}

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

	if (data.column % 2 != 0 || data.row % 2 != 0) {
		return false;
	}

	levelData = data;
	initLayout();

	return true;
}

void GameLevel::initLayout() {
	for (int i = 0; i < levelData.column; i++) {
		std::vector<Card*> r(levelData.row);
		cardsTable.push_back(r);
	}

	int bgColor = CCRANDOM_0_1() * 8;
	CardFactory factory;
	int number = 0, space = 40;
	for (int column = 0; column < levelData.column; column++) {
		for (int row = 0; row < levelData.row; row++) {
			Card* card = dynamic_cast<Card*>(factory.createCard(bgColor, number / 2));
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