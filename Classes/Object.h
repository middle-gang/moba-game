#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "cocos2d.h"
#include "Blood.h"
using namespace cocos2d;

class ObjectBase
{
public:
	ObjectBase()
	{
	}
	ObjectBase(int i,int j,int k,Vec2 pos,std::string str){
		health = i;
		attack = j;
		radium = k;
		Position = pos;
		Charac = Sprite::create(str);
	}
	
	bool InRange(Vec2 ene);
	bool Death();//判断是否死亡
	bool& isAttacking();
	
	int& getRadium();
	int getVelocity();
	int Money();
	int Attack(ObjectBase& ene);
	int& AttackPower();
	int& healthPower();//获得生命
	int& totalHealth();
	int HeroIdentifier=1;

	void Die();
	void BloodInit();
	void BeAttack(int n);//被造成伤害
	void setVelocity(int v);
	void Move(Vec2 dest);
	void revive();
	void setAttackingSpeed(float tms);
	void attachToSprite(Sprite* spr);
	void setImage(std::string str);
	void Kill_reward(ObjectBase& ene);
	void setSpawnPoint(Vec2 spawn);
	void Judge(float& jt);
	void setMoveablity(bool mab);
	void initBloodScale();
	void setFrame(std::string str);
	void bulletRemove();
	void setAnimeIdentifier(int i);
	void setAnimeIdentifierFromChoice(int i);
	void HeroSet(int i);
	void HeroInit(Sprite* player, Vec2 spawnP);

	float attackDelay();
	
	Vec2& getPosition();
	Sprite* getSprite();
	Sprite* getBullet();
	
	ProgressView* BloodView;

	int e_money = 300;
	int e_exp;
	int m_kill = 0;
	int m_death = 0;

	double DeadTime = 10;
	double waitTime = 0;
protected:
	int health;//生命值
	int nowHealth;
	int attack;//攻击力
	int power;//法术强度
	int radium;//攻击半径
	float velocity;//速度
	int m_money=0;
	int m_exp;
	int animeIdentifier;

	bool isAlive=true;
	bool attackingFlag=false;
	bool Moveable = true;

	float atkdelay=1;
	Vec2 Position;
	Vec2 Spawn;
	Sprite* Charac;
	Sprite* Blood=Sprite::create("blood.png");
	Sprite* Bar=Sprite::create("bar.png");
	Sprite* Bullet = Sprite::create("bulletTest.png");

	std::string frameSet;
};

#endif 
	