#pragma once

#include "cocos2d.h"
#include "ICard.h"
USING_NS_CC;

class Card : public ICard, public Node {
	Card();
	virtual ~Card();
protected:
	CardState state;
	CardData* data;
	CC_PROPERTY(Node*, frontImage, FrontImage);
	CC_PROPERTY(Node*, backImage, BackImage);
	void flipFromTo(Node* a, Node* b, const std::function<void()> &callback = nullptr);

public:
	CREATE_FUNC(Card);
	virtual void flipToFront(const std::function<void()> &callback = nullptr);
	virtual void flipToBack(const std::function<void()> &callback = nullptr);
	virtual CardState getCardState() const;
	virtual CardData* getCardData();
	virtual void setCardData(CardData* data);
};