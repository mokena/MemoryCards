#pragma once
#include "ICard.h"

class CardFactory {
public:
	ICard* createCard(int backId, int number);
};
