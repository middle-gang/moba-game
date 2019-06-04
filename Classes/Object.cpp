#include "Object.h"

bool ObjectBase::InRange(Vec2 ene) {
	if (radium > Position.distance(ene)) {
		return true;
	}
	return false;
}

void ObjectBase::Die() {
	isAlive = false;
	m_death++;
	Animation * animation = Animation::create();
	for (int i = 1; i <= 5; i++) {
		__String * frameName = __String::createWithFormat("CloseWarriorDie%d.png", i);
		log("frameName = %s", frameName->getCString());
		SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}

	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

	Animate * action = Animate::create(animation);

	Sequence* seqAct = Sequence::create(action, DelayTime::create(0.5),MoveTo::create(0, Vec2(-1000, -1000)), NULL);

	Charac->runAction(seqAct);

	if(BloodView!=nullptr) BloodView->setPosition(Vec2(-1000,-1000));
	Position = Vec2(-1000,-1000);
}

void ObjectBase::Kill_reward(ObjectBase& ene) {
	m_money += ene.e_money;
	m_exp += ene.e_exp;
}

bool ObjectBase::Death() {
	if (!isAlive) return true;
	return false;
}

void ObjectBase::BeAttack(int damage) {
	nowHealth -= damage;
	Blink* blink = Blink::create(0.1, 1);
	Charac->runAction(blink);
	if (health <= 0) {
		Die();
	}
}

int ObjectBase::Attack(ObjectBase& ene) {
	if (!attackingFlag) {
		attackingFlag = true;
		Charac->stopAllActions();
		Animation * animation = Animation::create();
		if (animeIdentifier == 1) {
			//Animation * animation = Animation::create();
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("BowmanAttack%d.png", i);
				log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (animeIdentifier == 2) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("SavageAttack%d.png", i);
				log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (animeIdentifier == 3) {
			for (int i = 1; i <= 4; i++) {
				__String * frameName = __String::createWithFormat("WizardAttack%d.png", i);
				log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (animeIdentifier == 5) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("CloseWarriorAttack%d.png", i);
				log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (animeIdentifier == 6) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("DistantWarriorAttack%d.png", i);
				log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}

		ene.BeAttack(attack);
		if (ene.healthPower() <= 0) {
			ene.Die();
		}

	}
	return attack;
}

void ObjectBase::setMoveablity(bool mab) {
	Moveable = mab;
}

void ObjectBase::Judge(float& jt) {
	if (jt > atkdelay) {
		attackingFlag = false;
		jt = 0;
	}
}

int& ObjectBase::AttackPower() {
	return attack;
}

void ObjectBase::revive() {
	isAlive = true;
	Charac->setPosition(Spawn);
	Position = Charac->getPosition();
	health = 100;
}

Sprite* ObjectBase::getSprite() {
	return Charac;
}

int ObjectBase::getVelocity() {
	return velocity;
}

void ObjectBase::setVelocity(int v) {
	velocity = v;
}

Vec2& ObjectBase::getPosition() {
	return Position;
}

int& ObjectBase::healthPower() {
	return nowHealth;
}

int& ObjectBase::totalHealth() {
	return health;
}

int& ObjectBase::getRadium() {
	return radium;
}

void ObjectBase::setImage(std::string str) {
	Charac = Sprite::create(str);
}

void ObjectBase::Move(Vec2 dest) {
	Charac->stopAllActions();
	float cost = dest.distance(Position)/velocity;
	Charac->runAction(MoveTo::create(cost, dest));

	Animation * animation = Animation::create();
	if (animeIdentifier == 1) {
		//Animation * animation = Animation::create();
		for (int i = 1; i <= 7; i++) {
			__String * frameName = __String::createWithFormat("BowmanRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}

	else if (animeIdentifier == 2) {
		for (int i = 1; i <= 6; i++) {
			__String * frameName = __String::createWithFormat("SavageRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (animeIdentifier == 3) {
		for (int i = 1; i <= 8; i++) {
			__String * frameName = __String::createWithFormat("WizardRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (animeIdentifier == 5) {
		for (int i = 1; i <= 8; i++) {
			__String * frameName = __String::createWithFormat("CloseWarriorRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (animeIdentifier == 6) {
		for (int i = 1; i <= 4; i++) {
			__String * frameName = __String::createWithFormat("DistantWarriorRun%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}

	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

}

int ObjectBase::Money() {
	return m_money;
}

void ObjectBase::setSpawnPoint(Vec2 spawn) {
	Spawn = spawn;
}

void ObjectBase::BloodInit() {
}

bool& ObjectBase::isAttacking() {
	return attackingFlag;
}

float ObjectBase::attackDelay() {
	return atkdelay;
}

void ObjectBase::attachToSprite(Sprite* spr) {
	Charac = spr;
}

void ObjectBase::setAttackingSpeed(float tms) {
	atkdelay = tms;
}

void ObjectBase::initBloodScale() {
	BloodView = new ProgressView();
	BloodView->setPosition(Vec2(0, 0));
	BloodView->setScale(0.05f);
	BloodView->setBackgroundTexture("bar.png");
	BloodView->setForegroundTexture("blood.png");
	BloodView->setTotalProgress(health);
	BloodView->setCurrentProgress(nowHealth);
	BloodView->setPosition(Charac->getPosition());
}

void ObjectBase::setFrame(std::string str) {
	frameSet = str;
}

Sprite* ObjectBase::getBullet() {
	return Bullet;
}

void ObjectBase::bulletRemove() {
	Bullet->setPosition(Vec2(-1000, -1000));
}

void ObjectBase::setAnimeIdentifier(int i) {
	animeIdentifier = i;
}