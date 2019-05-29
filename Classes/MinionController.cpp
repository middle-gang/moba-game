#include "MinionController.h"

Sprite* MinionController::NewMinion(int n) {
	ObjectBase minionBuf(minion_hp, minion_attack, minion_r, MinionSpawn, "qian.png");
	minionBuf.setVelocity(minion_v);
	minionBuf.getSprite()->setPosition(MinionSpawn);
	minion.push_back(minionBuf);
	return minionBuf.getSprite();
}

std::vector<ObjectBase>& MinionController::Container() {
	return minion;
}

bool MinionController::CheckAware(ObjectBase* Sub) {
	bool ck = false;
	for (int i = 0; i < minion.size(); i++) {
		log("%f", Sub->getPosition().distance(minion[i].getPosition()));
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