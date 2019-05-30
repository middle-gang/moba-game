#include "MinionController.h"

std::vector<ObjectBase>& MinionController::Container() {
	return minion;
}

Sprite* MinionController::NewMinion() {
	return nullptr;
}

bool MinionController::CheckAware(ObjectBase* Sub) {
	bool ck = false;
	for (int i = 0; i < minion.size(); i++) {
		//log("%f", Sub->getPosition().distance(minion[i].getPosition()));
		if (Sub->getPosition().distance(minion[i].getPosition())<minion_r) {
			Plan[i] = Sub->getPosition();
		}
		else {
			Plan[i] =Destination;
		}
	}
	return ck;
}

void MinionController::Stop() {
	for (int i = 0; i < minion.size(); i++) {
		minion[i].getSprite()->stopAllActions();
	}
}

void MinionController::MoveAndAttack() {
	for (int i = 0; i < minion.size(); i++) {
		minion[i].getSprite()->runAction(MoveTo::create(
		Plan[i].distance(minion[i].getPosition()) / minion_v,
		Plan[i]));
	}
}