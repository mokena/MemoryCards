#pragma once

#include <functional>
#include "CardData.h"
#include "CardState.h"

class ICard {
public:
	virtual void flipToFront(const std::function<void()> &callback=nullptr) = 0;
	virtual void flipToBack(const std::function<void()> &callback = nullptr) = 0;
	virtual CardState getCardState() const = 0;
	virtual CardData* getCardData() = 0;
	virtual void setCardData(CardData data) = 0;
};

