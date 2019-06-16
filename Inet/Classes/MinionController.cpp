#include "MinionController.h"

std::vector<ObjectBase>& MinionController::Container() {
	return minion;
}

Sprite* MinionController::NewMinion() {
	return nullptr;
}

void MinionController::Judge(int i, float delt) {
	attackingDelayTime[i] += delt;
	if (attackingDelayTime[i] > 1) {
		attackingDelayTime[i] = 0;
		minion[i].isAttacking() = false;
	}
}

bool MinionController::CheckAware(ObjectBase& Sub) {
	bool ck = false;
	for (int i = 0; i < minion.size(); i++) {
		if (Sub.getPosition().distance(minion[i].getPosition())<200) {
			Plan[i] = Sub.getPosition();
		}
		else {
			Plan[i] =Destination;
		}
	}
	log("%f %f", Plan[0].x, Plan[0].y);
	return ck;
}

void MinionController::Stop() {
	for (int i = 0; i < minion.size(); i++) {
		minion[i].getSprite()->stopAllActions();
	}
}

void MinionController::MoveToTarget() {
	for (int i = 0; i < minion.size(); i++) {
		if (minion[i].healthPower() <= 0) continue;
		minion[i].getSprite()->stopAllActions();
		
		minion[i].Move(Plan[i]);
	}
}