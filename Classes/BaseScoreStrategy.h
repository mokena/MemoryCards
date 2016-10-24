#pragma once
#include "ScoreData.h"
#include "CardData.h"

class BaseScoreStrategy {

public:
	virtual void execute(ScoreData* scoreData, CardData* dataA, CardData* dataB)=0;
};
