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
		
		minion[i].getSprite()->runAction(MoveTo::create(
		Plan[i].distance(minion[i].getPosition()) / minion_v,
		Plan[i]));

		Animation * animation = Animation::create();
		for (int i = 1; i <= 6; i++) {
			__String * frameName = __String::createWithFormat("CloseWarriorRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.03f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		this->minion[i].getSprite()->runAction(RepeatForever::create(action));
	}
}