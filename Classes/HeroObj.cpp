#include "HeroObj.h"

void HeroObj::setHomerecover() {
	HomeHPRecover = true;
	HomeMPRecover = true;
}

void HeroObj::removeHomerecover() {
	HomeHPRecover = false;
	HomeMPRecover = false;
}

const HeroObj HeroObj::operator +(const EquipmentData equip) {
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

const HeroObj HeroObj::operator -(const EquipmentData equip) {
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

void HeroObj::Buy(int EquipNumber) {
	//log("EquipN=%d", EquipNumber);
	EquipmentData buf = EquipList.findEquip(EquipNumber);
	if (buf.ingriEquip.size() != 0) {
		int nonSubst = 0;
		std::vector<int> appList;
		int virtualMoney = m_money;
		for (int i = 0; i < 6; i++) {
			if (equip[i] != -1) {
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

void HeroObj::Sale(int locNumber,int Equipnumber) {
	EquipmentData buf = EquipList.findEquip(Equipnumber);
	if (equip[locNumber] != -1) {
		equip[locNumber] = -1;
		m_money += buf.sellmoney;
		this->operator-(buf);
	}
}

void HeroObj::setMoney(int n) {
	m_money = n;
}

void HeroObj::LvUp() {
	if (m_exp >= Exp[MyLevel - 1] && MyLevel < 18) {

		m_exp = 0;
		MyLevel++;

		int h = HeroIdentifier - 1;
		attack += HeroData[h][1];
		atkSpeedLevel += HeroData[h][3];
		health += HeroData[h][5];
		healthRecover += HeroData[h][7];
		armor += HeroData[h][9];
		magicDenfence += HeroData[h][11];
		magicpoint += HeroData[h][13];
		magicpointRecover += HeroData[h][15];
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

void HeroObj::ExpAndMoneyIncrease(float delta) {
	ExpAndMoneytimer += delta;
	if (ExpAndMoneytimer >= 1) {
		ExpAndMoneytimer = 0;
		m_money += 3;
		t_money += 3;
		m_exp += 1;
		LvUp();
	}
}

void HeroObj::BackToSpawn() {
	Charac->setPosition(Spawn);
}

void HeroObj::Interrupt() {
	isBacking = false;
}

void HeroObj::JudgeBack(float& time, float del) {
	time += del;
	if (time > backSpawn) {
		BackToSpawn();
		isBacking = false;
	}
}

bool& HeroObj::CheckBacking() {
	return isBacking;
}

/*void HeroObj::BeAttack(float damage) {
	nowHealth -= damage * 602 / (602 + armor);
	if (isBacking) {
		Interrupt();
	}
	if (nowHealth <= 0) {
		Die();
	}
}*/

//int HeroObj::Attack(ObjectBase& ene) {
//	if (!attackingFlag) {
//		attackingFlag = true;
//		Charac->stopAllActions();
//		Animation * animation = Animation::create();
//		if (HeroIdentifier == 1) {
//			//Animation * animation = Animation::create();
//			for (int i = 1; i <= 3; i++) {
//				__String * frameName = __String::createWithFormat("BowmanAttack%d.png", i);
//				//log("frameName = %s", frameName->getCString());
//				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
//				animation->addSpriteFrame(spriteFrame);
//			}
//
//			animation->setDelayPerUnit(0.08f);
//			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态
//
//			Animate * action = Animate::create(animation);
//			Charac->runAction(action);
//		}
//		else if (HeroIdentifier == 2) {
//			for (int i = 1; i <= 3; i++) {
//				__String * frameName = __String::createWithFormat("SavageAttack%d.png", i);
//				//log("frameName = %s", frameName->getCString());
//				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
//				animation->addSpriteFrame(spriteFrame);
//			}
//
//			animation->setDelayPerUnit(0.08f);
//			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态
//
//			Animate * action = Animate::create(animation);
//			Charac->runAction(action);
//		}
//		else if (HeroIdentifier == 3) {
//			for (int i = 1; i <= 4; i++) {
//				__String * frameName = __String::createWithFormat("WizardAttack%d.png", i);
//				//log("frameName = %s", frameName->getCString());
//				SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
//				animation->addSpriteFrame(spriteFrame);
//			}
//
//			animation->setDelayPerUnit(0.08f);
//			animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态
//
//			Animate * action = Animate::create(animation);
//			Charac->runAction(action);
//		}
//
//		if (attackStrength) {
//			attackStrength = false;
//			ene.BeAttack(attack*1.2);
//		}
//		else ene.BeAttack(attack);
//		
//		if (ene.healthPower() <= 0) {
//			ene.Die();
//			m_kill++;
//			Kill_reward(ene);
//		}
//
//	}
//	return attack;
//}

float HeroObj::PhysicBloodSuck()
{
	return physicBloodSuck;
}

float HeroObj::MagicBloodSuck()
{
	return magicBloodSuck;
}

float HeroObj::WaitLessen()
{
	return waitLessen;
}

//void HeroObj::Die() {
//	isAlive = false;
//	m_death++;
//	
//	Sequence* seqAct = Sequence::create(MoveTo::create(0, Vec2(-1000, -1000)), NULL);
//	Charac->runAction(seqAct);
//
//	if (BloodView != nullptr) BloodView->setPosition(Vec2(-1000, -1000));
//	Position = Vec2(-1000, -1000);
//}

bool HeroObj::QIsUsed() {
	return Qflag;
}

bool HeroObj::WIsUsed() {
	return Wflag;
}

bool HeroObj::EIsUsed() {
	return Eflag;
}

void HeroObj::Ability1st() {
	if (QIsUsed()) return;
	if (HeroIdentifier == 2) {
		log("Q activate!");
		velocity += 20;
		Qrecover = true;
		attackStrength = true;
		Qflag = true;
		attackingFlag = false;//取消后摇
	}
	if (HeroIdentifier == 1) {
		attackingSpeed += 2;
		JudgeAttackSpeedLevel();
		Qrecover = true;
		Qflag = true;
	}
	if (HeroIdentifier == 3) {
		if (QActivate) {
			for (int i = 0; i < Qtarget.size(); i++) {
				Qtarget[i].BeAttack(50 + power * 1.1);
				if (Qtarget[i].healthPower() <= 0) {
					Kill_reward(Qtarget[i]);
				}
			}
			Qtarget.clear();
			QBoundJudge = false;
			Qflag = true;
			return;
		}
		QBoundJudge = true;
	}
}

void HeroObj::Qjudge(float delta) {
	Qtimer += delta;
	if (HeroIdentifier == 2) {
		if (Qtimer >= 3 && Qrecover) {
			velocity -= 20;
			Qrecover = false;
			attackStrength = false;
		}
		if (Qtimer >= 5) {
			Qflag = false;
			Qtimer = 0;
		}
	}
	if (HeroIdentifier == 1) {
		if (Qtimer >= 3 && Qrecover) {
			attackingSpeed -= 2;
			Qrecover = false;
			JudgeAttackSpeedLevel();
		}
		if (Qtimer == 6) {
			Qflag = false;
			Qtimer = 0;
		}
	}
	if (HeroIdentifier == 3) {
		if (Qtimer >= 5) {
			Qflag = false;
			Qtimer = 0;
		}
	}
}

void HeroObj::Ability2st() {
	if (WIsUsed()) return;
	if (HeroIdentifier == 2) {
		armor += 30;
		magicDenfence += 50;
		Wrecover = true;
		Wflag = true;
	}
	if (HeroIdentifier == 1) {
		if (WActivate) {
			for (int i = 0; i < Wtarget.size(); i++) {
				Wtarget[i].BeAttack(attack*0.8);
			}
			Wtarget.clear();
			WBoundJudge = false;
			Wflag = true;
			return;
		}
		WBoundJudge = true;				//开启E的范围判断，类似智能施法
	}
	if (HeroIdentifier == 3) {
		if (WActivate) {
			for (int i = 0; i < Wtarget.size(); i++) {
				Wtarget[i].BeAttack(1000 + power * 0.8);
				if (Wtarget[i].healthPower() <= 0) {
					Kill_reward(Wtarget[i]);
				}
				log("W launch on %d", Wtarget[i].HeroIdentifier);
				//这里还需要加入眩晕效果
			}
			Wtarget.clear();
			WBoundJudge = false;
			Wflag = true;
			return;
		}
		WBoundJudge = true;
	}
}

void HeroObj::Wjudge(float delta) {
	Wtimer += delta;
	if (HeroIdentifier == 2) {
		if (Wtimer >= 3 && Wrecover) {
			armor -= 30;
			magicDenfence -= 50;
			Wrecover = false;
			attackStrength = false;
		}
		if (Wtimer >= 6) {
			Wflag = false;
			Wtimer = 0;
		}
	}
	if (HeroIdentifier == 1) {
		if (Wtimer >= 6) {
			Wflag = false;
			Wtimer = 0;
		}
	}
	if (HeroIdentifier == 3) {
		if (Wtimer >= 6) {
			Wflag = false;
			Wtimer = 0;
		}
	}
}

void HeroObj::Ability3st() {
	if (EIsUsed()) return;
	if (HeroIdentifier == 2) {
		if (EActivate) {
			Charac->runAction(MoveTo::create(0.2, Etarget->getPosition()));
			Etarget->BeAttack(attack*1.5);
			if (Etarget->healthPower() <= 0) {
				Kill_reward(*Etarget);
			}
			EBoundJudge = false;
			Eflag = true;
			return;
		}
		EBoundJudge = true;				//开启E的范围判断，类似智能施法
	}
	if (HeroIdentifier == 1) {
	}
	if (HeroIdentifier == 3) {
		Qflag = false;
		Wflag = false;
		Qtimer = 0;
		Wtimer = 0;//刷新所有技能时间
		Wflag = true;
	}
}

void HeroObj::Ejudge(float delta) {
	Etimer += delta;
	if (HeroIdentifier == 2) {
		if (Etimer >= 15) {
			Eflag = false;
			Etimer = 0;
		}
	}
	if (HeroIdentifier == 1) {
		if (Etimer >= 15) {
			Eflag = false;
			Etimer = 0;
		}
	}
	if (HeroIdentifier == 3) {
		if (Etimer >= 25) {
			Eflag = false;
			Etimer = 0;
		}
	}
}

int HeroObj::Level() {
	return MyLevel;
}

int HeroObj::tMoney() {
	return t_money;
}

int HeroObj::Money() {
	return m_money;
}

void HeroObj::Kill_reward(ObjectBase& ene) {
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

int HeroObj::Attack(ObjectBase& ene) {
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
			Kill_reward(ene);
		}
	}
	return attack;
}