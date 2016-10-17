#include "CardFactory.h"
#include "Cocos2d.h"
#include "ui/CocosGUI.h"
#include "Card.h"

USING_NS_CC;

ICard* CardFactory::createCard(int backId, int number) {
	int cardSize = 256; //back image's width and height;

	if (backId < 0 || backId >= 8) { backId = 0; }
	
	//front side
	Node* frontImg = Node::create();
	auto fmg = Sprite::create("card_front.png");
	cardSize = fmg->getContentSize().width;
	frontImg->setContentSize(Size(cardSize, cardSize));
	frontImg->addChild(fmg);
	auto numberText = ui::TextAtlas::create(StringUtils::format("%d", number), "card_number.png",
		140, 140, "0");
	frontImg->addChild(numberText);

	//back side
	int bx = (backId % 2)*cardSize;
	int by = (backId / 2)*cardSize;
	auto backImg = Sprite::create("card_back.png", Rect(bx, by, cardSize, cardSize));

	CardData data = {};
	data.number = number;

	Card* card = Card::create();
	card->setCardData(data);
	card->setFrontImage(frontImg);
	card->setBackImage(backImg);
	card->setContentSize(backImg->getContentSize());

	return card;
}