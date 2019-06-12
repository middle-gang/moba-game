#include "HeroObj.h"

void Hero::setHomerecover() {
	HomeHPRecover = true;
	HomeMPRecover = true;
}

void Hero::removeHomerecover() {
	HomeHPRecover = false;
	HomeMPRecover = false;
}

const Hero Hero::operator +(const EquipmentData equip) {
	health += equip.health;
	magicpoint += equip.magicpoint;
	healthRecover += equip.healthRecover;
	magicpointRecover += equip.magicpointRecover;
	attack += equip.attack;
	power += equip.power;

	armor += equip.armor;
	magicDenfence += equip.magicDenfence;
	armorIgnore += equip.armorIgnore;
	magicdenfenceIgnore += equip.armorIgnore;
	physicBloodSuck += equip.physicBloodSuck;
	magicBloodSuck += equip.magicBloodSuck;
	waitLessen += equip.waitLessen;

	velocity += (equip.velocity*velocity);
	attackingSpeed += attackingSpeed;
	JudgeAttackSpeedLevel();
	return *this;
}

const Hero Hero::operator -(const EquipmentData equip) {
	health -= equip.health;
	magicpoint -= equip.magicpoint;
	healthRecover -= equip.healthRecover;
	magicpointRecover -= equip.magicpointRecover;
	attack -= equip.attack;
	power -= equip.power;

	armor -= equip.armor;
	magicDenfence -= equip.magicDenfence;
	armorIgnore -= equip.armorIgnore;
	magicdenfenceIgnore -= equip.armorIgnore;
	physicBloodSuck -= equip.physicBloodSuck;
	magicBloodSuck -= equip.magicBloodSuck;
	waitLessen -= equip.waitLessen;

	velocity -= (equip.velocity*velocity);//??
	attackingSpeed -= attackingSpeed;
	JudgeAttackSpeedLevel();
	return *this;
}

void Hero::Buy(int EquipNumber) {
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

		if (virtualMoney - buf.buymoney >= 0) {
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

void Hero::Sale(int locNumber) {
	if (equip[locNumber] != -1) {
		equip[locNumber] = -1;
	}
}

void Hero::setMoney(int n) {
	m_money = n;
}

void Hero::LvUp() {
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

void Hero::ExpAndMoneyIncrease(float delta) {
	ExpAndMoneytimer += delta;
	if (ExpAndMoneytimer >= 1) {
		ExpAndMoneytimer = 0;
		m_money += 3;
		t_money += 3;
		m_exp += 1;
	}
}

void Hero::BackToSpawn() {
	Charac->setPosition(Spawn);
}

void Hero::Interrupt() {
	isBacking = false;
}

void Hero::JudgeBack(float& time, float del) {
	time += del;
	if (time > backSpawn) {
		BackToSpawn();
		isBacking = false;
	}
}

bool& Hero::CheckBacking() {
	return isBacking;
}

void Hero::Kill_reward(ObjectBase& ene) {
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

void Hero::BeAttack(float damage) {
	nowHealth -= damage * 602 / (602 + armor);
	if (isBacking) {
		Interrupt();
	}
	if (nowHealth <= 0) {
		Die();
	}
}

int Hero::Attack(ObjectBase& ene) {
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
		if (attackStrengh)
			ene.BeAttack(attack + attackplus);
		else
			ene.BeAttack(attack);
		if (ene.healthPower() <= 0) {
			ene.Die();
			m_kill++;
			Kill_reward(ene);
		}

	}
	return attack;
}

void Hero::SavageQ()
{
	if (QAvail)
	{
		attackStrengh = true;
		velocity += 30;
		QAvail = false;
	}
}
void Hero::SavageQJudge(float delta)
{
	Qtimer += delta;
	if (Qtimer >= 3) {
		velocity -= 30;
		attackStrengh = false;
	}
	if (Qtimer >= 5) {
		QAvail = true;
		Qtimer = 0;
	}
}

void Hero::SavageW()
{
	if (WAvail)
	{
		armor += 50;
		magicDenfence += 50;
		WAvail = false;
	}
}

void Hero::SavageWJudge(float delta)
{
	Wtimer += delta;
	if (Wtimer >= 3) {
		armor -= 50;
		magicDenfence -= 50;
	}
	if (Wtimer >= 5) {
		WAvail = true;
		Wtimer = 0;
	}
}

void Hero::SavageE()
{
	if (EAvail)
	{
		EAvail = false;
		Eflag = true;
	}
}

void Hero::SavageEJudge(float delta)
{
	Etimer += delta;
	if (Etimer >= 5) {
		Etimer = 0;
		EAvail = true;
	}
}

float Hero::PhysicBloodSuck()
{
	return physicBloodSuck;
}

float Hero::MagicBloodSuck()
{
	return magicBloodSuck;
}

float Hero::WaitLessen()
{
	return waitLessen;
}

void Hero::Die() {
	isAlive = false;
	m_death++;
	
	Sequence* seqAct = Sequence::create(MoveTo::create(0, Vec2(-1000, -1000)), NULL);
	Charac->runAction(seqAct);

	if (BloodView != nullptr) BloodView->setPosition(Vec2(-1000, -1000));
	Position = Vec2(-1000, -1000);
}