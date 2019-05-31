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
	bool Death();//�ж��Ƿ�����
	bool& isAttacking();
	
	int& getRadium();
	int getVelocity();
	int Money();
	int Attack(ObjectBase& ene);
	int& AttackPower();
	int& healthPower();//�������

	void Die();
	void BloodInit();
	void BeAttack(int n);//������˺�
	void setVelocity(int v);
	void Move(Vec2 dest);
	void revive();
	void setAttackingSpeed(float tms);
	void attachToSprite(Sprite* spr);
	void setImage(std::string str);
	void Kill_reward(ObjectBase& ene);
	void setSpawnPoint(Vec2 spawn);
	void Judge(float& jt);

	float attackDelay();
	
	Vec2& getPosition();
	Sprite* getSprite();
	
	ProgressView* BloodView;

	int e_money = 300;
	int e_exp;
	int m_kill = 0;
	int m_death = 0;

	double DeadTime = 10;
	double waitTime = 0;
protected:
	int health;//����ֵ
	int attack;//������
	int power;//����ǿ��
	int radium;//�����뾶
	float velocity;//�ٶ�
	int m_money=0;
	int m_exp;


	bool isAlive=true;
	bool attackingFlag=false;

	float atkdelay=1;
	Vec2 Position;
	Vec2 Spawn;
	Sprite* Charac;
	Sprite* Blood=Sprite::create("blood.png");
	Sprite* Bar=Sprite::create("bar.png");
};

#endif // __AVENE_SCENE_H__
	