#include "ScoreStrategy.h"

void ScoreStrategy::execute(ScoreData* scoreData, CardData* dataA, CardData* dataB) {
	if (dataA == nullptr || dataB == nullptr || scoreData == nullptr) return;

	if (dataA->number == dataB->number) {
		continus++;
		scoreData->score += 100 * continus;
		scoreData->energy += 100;
		if (continus > scoreData->maxContinuous) {
			scoreData->maxContinuous = continus;
		}
	}
	else {
		continus = 0;
		if (dataA->flipCount == 0 && dataB->flipCount == 0) {
		}
		else {
			scoreData->energy -= 100;
		}
		dataA->flipCount++;
		dataB->flipCount++;
	}
}