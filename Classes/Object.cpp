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
	Charac->setPosition(Vec2(-10000,-10000));
	Position = Charac->getPosition();
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
	health -= damage;
	Blink* blink = Blink::create(0.01, 1);
	Charac->runAction(blink);
	if (health <= 0) {
		Die();
	}
}

int ObjectBase::Attack(ObjectBase& ene) {
	if (InRange(ene.getPosition())&&!attackingFlag) {
		attackingFlag = true;
		Charac->stopAllActions();
		ene.BeAttack(attack);
		if (ene.healthPower() <= 0) {
			ene.Die();
		}
	}
	return attack;
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