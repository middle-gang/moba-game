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
	Sequence* seqAct = Sequence::create(MoveTo::create(0, Vec2(-1000, -1000)), NULL);
	Charac->runAction(seqAct);

	if(BloodView!=nullptr) BloodView->setPosition(Vec2(-1000,-1000));
	Position = Vec2(-1000,-1000);
}

void ObjectBase::Kill_reward(ObjectBase& ene) {
	if (ene.HeroIdentifier <= 3) {

	}
	else if (ene.HeroIdentifier == 5) {
		m_exp += 9;
		m_money += 35;
		t_money += 35;
		LvUp();
	}
	else if (ene.HeroIdentifier == 6) {
		m_exp += 7;
		m_money += 25;
		t_money += 25;
		LvUp();
	}
}

bool ObjectBase::Death() {
	if (!isAlive) return true;
	return false;
}

void ObjectBase::BeAttack(float damage) {
	nowHealth -= damage*602/(602+armor);
	if (isBacking) Interrupt();
	if (nowHealth <= 0) {
		Die();
	}
}

int ObjectBase::Attack(ObjectBase& ene) {
	if (!attackingFlag) {
		attackingFlag = true;
		Charac->stopAllActions();
		Animation * animation = Animation::create();
		if (HeroIdentifier == 1) {
			//Animation * animation = Animation::create();
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("BowmanAttack%d.png", i);
				//log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (HeroIdentifier == 2) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("SavageAttack%d.png", i);
				//log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (HeroIdentifier == 3) {
			for (int i = 1; i <= 4; i++) {
				__String * frameName = __String::createWithFormat("WizardAttack%d.png", i);
				//log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (HeroIdentifier == 5) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("CloseWarriorAttack%d.png", i);
				//log("frameName = %s", frameName->getCString());
				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation->addSpriteFrame(spriteFrame);
			}

			animation->setDelayPerUnit(0.08f);
			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

			Animate * action = Animate::create(animation);
			Charac->runAction(action);
		}
		else if (HeroIdentifier == 6) {
			for (int i = 1; i <= 3; i++) {
				__String * frameName = __String::createWithFormat("DistantWarriorAttack%d.png", i);
				//log("frameName = %s", frameName->getCString());
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
			if(HeroIdentifier <= 3) Kill_reward(ene);
		}

	}
	return attack;
}


void ObjectBase::setMoveablity(bool mab) {
	Moveable = mab;
}

void ObjectBase::JudgeAttack(float& jt) {
	if (jt > atkdelay) {
		attackingFlag = false;
		jt = 0;
	}
}

float& ObjectBase::AttackPower() {
	return attack;
}

void ObjectBase::revive() {
	isAlive = true;
	Charac->setPosition(Spawn);
	Position = Charac->getPosition();
	nowHealth =health ;
	nowMagicpoint = magicpoint;
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

void ObjectBase::changeVeclocity(int v)
{
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

//void ObjectBase::changeTotalHealth(int h)
//{
//}

int& ObjectBase::getRadium() {
	return radium;
}

void ObjectBase::Move(Vec2 dest) {
	Charac->stopAllActions();
	float cost = dest.distance(Position)/velocity;
	Charac->runAction(MoveTo::create(cost, dest));

	Animation * animation = Animation::create();
	if (HeroIdentifier == 1) {
		//Animation * animation = Animation::create();
		for (int i = 1; i <= 7; i++) {
			__String * frameName = __String::createWithFormat("BowmanRun%d.png", i);
			//log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}

	else if (HeroIdentifier == 2) {
		for (int i = 1; i <= 6; i++) {
			__String * frameName = __String::createWithFormat("SavageRun%d.png", i);
			//log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (HeroIdentifier == 3) {
		for (int i = 1; i <= 8; i++) {
			__String * frameName = __String::createWithFormat("WizardRun%d.png", i);
			//log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (HeroIdentifier == 5) {
		for (int i = 1; i <= 8; i++) {
			__String * frameName = __String::createWithFormat("CloseWarriorRun%d.png", i);
			//log("frameName = %s", frameName->getCString());
			SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.08f);
		animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

		Animate * action = Animate::create(animation);
		Charac->runAction(action);
	}
	else if (HeroIdentifier == 6) {
		for (int i = 1; i <= 4; i++) {
			__String * frameName = __String::createWithFormat("DistantWarriorRun%d.png", i);
			//log("frameName = %s", frameName->getCString());
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

int ObjectBase::tMoney()
{
	return t_money;
}

int ObjectBase::Level()
{
	return MyLevel;
}

void ObjectBase::setSpawnPoint(Vec2 spawn) {
	Spawn = spawn;
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
	attackingSpeed = tms;
	atkdelay = 1 / attackingSpeed;
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

Sprite* ObjectBase::getBullet() {
	return Bullet;
}

void ObjectBase::setAnimeIdentifier(int i) {
	HeroIdentifier = i;
}

void ObjectBase::HeroInit(Sprite*& spr,Vec2 spawnP) {
	if(HeroIdentifier ==1) spr = Sprite::createWithSpriteFrameName("BowmanRun1.png");
	if(HeroIdentifier ==2) spr = Sprite::createWithSpriteFrameName("SavageRun1.png");
	if(HeroIdentifier ==3) spr = Sprite::createWithSpriteFrameName("WizardRun1.png");
	Charac = spr;
	spr->setPosition(spawnP);
	setSpawnPoint(spawnP);
	int h = HeroIdentifier - 1;
	attack = HeroData[h][0];
	atkSpeedLevel = HeroData[h][2];
	health = HeroData[h][4];
	nowHealth = health;
	healthRecover = HeroData[h][6];
	armor = HeroData[h][8];
	magicDenfence = HeroData[h][10];
	magicpoint = HeroData[h][12];
	magicpointRecover = HeroData[h][14];
	velocity = HeroData[h][16];
	getRadium() = 200;
	initBloodScale();
}

void ObjectBase::JudgeBack(float& time, float del) {
	time += del;
	if (time > backSpawn) {
		BackToSpawn();
		isBacking = false;
	}
}

void ObjectBase::BackToSpawn() {
	Charac->setPosition(Spawn);
}

bool& ObjectBase::CheckBacking() {
	return isBacking;
}

void ObjectBase::Interrupt() {
	isBacking = false;
}

void ObjectBase::JudgeAttackSpeedLevel() {
	bool limMax = false;
	//顺序判断
	for (int i = 0; i < 11; i++) {
		if (atkSpeedLevel < AtkSpeed[HeroIdentifier-1][i]) {
			atkdelay = 60 / (HeroAtkSpeedLim[HeroIdentifier-1][i-1]);
			limMax = true;
			return;
		}
	}
	if (!limMax) {
		//攻速达到最大
		atkdelay = 60 / (HeroAtkSpeedLim[HeroIdentifier - 1][10]);
	}
}

void ObjectBase::HealthRebound(float delta) {
	if (!Death()&&nowHealth<health) {
		HPrecoverTimer += delta;
		if (HPrecoverTimer >= 1) {
			nowHealth += healthRecover / 5;
			if (HomeHPRecover) nowHealth += health / 10;
			if (nowHealth > health) nowHealth = health;
			HPrecoverTimer=0;
		}
	}
}

void ObjectBase::MagicRebound(float delta) {
	if (!Death() && nowMagicpoint < magicpoint) {
		MPrecoverTimer += delta;
		if (MPrecoverTimer >= 1) {
			nowMagicpoint += magicpointRecover / 5;
			if (HomeMPRecover) nowMagicpoint += magicpoint / 10;
			if (nowMagicpoint > magicpoint) nowMagicpoint = magicpoint;
			MPrecoverTimer = 0;
		}
	}
}

void ObjectBase::setArmor(float ar) {
	armor = ar;
}

void ObjectBase::SetAtkSpeedLevel(int n) {
	atkSpeedLevel = n;
}

void ObjectBase::LvUp() {
	if (m_exp >= Exp[MyLevel - 1]) {
		int h = HeroIdentifier - 1;
		attack += HeroData[h][1];
		atkSpeedLevel += HeroData[h][3];
		health += HeroData[h][5];
		healthRecover += HeroData[h][7];
		armor += HeroData[h][9];
		magicDenfence += HeroData[h][11];
		magicpoint += HeroData[h][13];
		magicpointRecover += HeroData[h][15];
		m_exp = 0;
		if (nowHealth + HeroData[h][5] < health) {
			nowHealth += HeroData[h][5];
		}
		else {
			nowHealth = health;
		}
		if (nowMagicpoint + HeroData[h][13] < magicpoint) {
			nowMagicpoint += HeroData[h][13];
		}
		else {
			nowMagicpoint = magicpoint;
		}
	}
}

void ObjectBase::ExpAndMoneyIncrease(float delta) {
	ExpAndMoneytimer += delta;
	if (ExpAndMoneytimer >= 1) {
		ExpAndMoneytimer = 0;
		m_money += 3;
		m_exp += 1;
	}
}

int ObjectBase::ObjectType() {
	return HeroIdentifier;
}

float ObjectBase::AttackSpeed()
{
	return attackingSpeed;
}

float ObjectBase::Power()
{
	return power;
}

int ObjectBase::MagicPoint()
{
	return magicpoint;
}

float ObjectBase::Armor()
{
	return armor;
}

float ObjectBase::MagicDefence()
{
	return magicDenfence;
}

int ObjectBase::HealthRecover()
{
	return healthRecover;
}

int ObjectBase::MagicPointRecover()
{
	return magicpointRecover;
}

float ObjectBase::ArmorIgnore()
{
	return armorIgnore;
}

float ObjectBase::MagicDefenseIgnore()
{
	return magicdenfenceIgnore;
}

float ObjectBase::PhysicBloodSuck()
{
	return physicBloodSuck;
}

float ObjectBase::MagicBloodSuck()
{
	return magicBloodSuck;
}

float ObjectBase::WaitLessen()
{
	return waitLessen;
}

float ObjectBase::E_Armor()
{
	return 0.0f;
}

float ObjectBase::E_MagicDenfense()
{
	return 0.0f;
}

int ObjectBase::E_Kill()
{
	return 0;
}

int ObjectBase::E_Level()
{
	return 0;
}

Vec2 ObjectBase::SpawnPoint() {
	return Spawn;
}

void ObjectBase::setHomerecover() {
	HomeHPRecover = true;
	HomeMPRecover = true;
}

void ObjectBase::removeHomerecover() {
	HomeHPRecover = false;
	HomeMPRecover = false;
}

void ObjectBase::Buy(int EquipNumber) {
	//log("EquipN=%d", EquipNumber);
	EquipmentData buf = EquipList.findEquip(EquipNumber);
	if (buf.ingriEquip.size() != 0) {
		int nonSubst = 0;
		std::vector<int> appList;
		int virtualMoney = m_money;
		for (int i = 0; i < 6; i++) {
			if (equip[i] == -1) {
				nonSubst++;
				continue;
			}
			for (int j = 0; j < buf.ingriEquip.size(); j++) {
				if (equip[i] == buf.ingriEquip[j]) {
					appList.push_back(i);
					virtualMoney += EquipList.findEquip(equip[i]).buymoney;
				}
			}
		}
		if (nonSubst == 6) return;

		if(virtualMoney - buf.buymoney >= 0) {
			m_money = virtualMoney;
			for (int i = 0; i < appList.size(); i++) {
				this->operator -(EquipList.findEquip(equip[appList[i]]));
				equip[appList[i]] = -1;
			}
		}
		else {
			return;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (equip[i] == -1) {
			if (m_money >= buf.buymoney) {
				equip[i] = EquipNumber;
				m_money -= buf.buymoney;
				this->operator+(buf);
				break;
			}
		}
	}
}

void ObjectBase::Sale(int locNumber) {
	if (equip[locNumber] != -1) {
		equip[locNumber] = -1;
	}
}

void ObjectBase::setMoney(int n) {
	m_money = n;
}


void ObjectBase::Read(InputMemoryBitStream& stream) const {
	stream.Read(health);
	straem.Read(attack);
	stream.Read(radium);
	stream.Read(Position);
	stream.Read(Charac);
}
	
	
void ObjectBase::Write(OutputMemoryBitStream& stream) {
	stream.Write(health);
	straem.Write(attack);
	stream.Write(radium);
	stream.Write(Position);
	stream.Write(Charac);
}
