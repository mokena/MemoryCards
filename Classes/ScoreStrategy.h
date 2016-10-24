#pragma once

#include "BaseScoreStrategy.h"

class ScoreStrategy : public BaseScoreStrategy {

public:
	int continus;
	virtual void execute(ScoreData* scoreData, CardData* dataA, CardData* dataB);
};
