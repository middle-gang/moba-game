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
	
	bool InRange(Vec2 ene);		//判断ene对象是否在攻击范围内
	bool Death();                //判断人物是否死亡。死亡：true，存活false
	bool& isAttacking();		//判断人物是否处于攻击冷却期（两次攻击之间的间隔）
	bool& CheckBacking();		//判断人物是否在回城
	
	int& getRadium();			//以引用的形式返回人物的攻击范围
	int getVelocity();			//获取人物的移动速度
	int Money();				//人物的金钱
	int Attack(ObjectBase& ene);	//攻击函数，造成伤害，动画，击杀
	int& AttackPower();				//引用形式返回攻击力
	int& healthPower();				//引用形式返回目前生命
	int& totalHealth();				//引用形式返回总生命值
	void changeTotalHealth(int h);       //改变总生命值

	void Die();					//死亡的时候调用
	void BeAttack(int n);		//被造成伤害（Attack中调用）
	void setVelocity(int v);	//设置速度
	void changeVeclocity(int v);   //改变速度
	void Move(Vec2 dest);		//移动函数，参数为坐标
	void revive();				//复活到复活点
	void setAttackingSpeed(float tms);//设置攻击速度（每秒攻击的次数）
	void attachToSprite(Sprite* spr);//把ObjectBase类与特定对象对接
	void Kill_reward(ObjectBase& ene);//击杀获得奖励（金钱经验）
	void setSpawnPoint(Vec2 spawn);//设置出生点
	void JudgeAttack(float& jt);	//传入参数计时值 jt 假如到达攻击间隔可以再次攻击并且将 jt 归零
	void setMoveablity(bool mab);	//设置是否为可移动对象（塔和水晶不可移动）
	void initBloodScale();			//初始化血条
	void setAnimeIdentifier(int i); //设置动画标签
	void HeroInit(Sprite*& spr,Vec2 spawnP); //英雄的初始化，精灵的绑定和属性值初始化
	void BackToSpawn();				//回到出生点
	void Interrupt();				//打断回城
	void JudgeBack(float& time, float del);	//传入参数计时值 time 假如回城时间到就回城并且将 time 归零

	float attackDelay();		//返回攻击延迟时间
	
	Vec2& getPosition();		//获取位置
	Sprite* getSprite();		//获取人物精灵
	Sprite* getBullet();		//获取子弹（有待设计）
	
	ProgressView* BloodView;	//血条

    int e_tower = 0;            //推倒对方塔数
	int e_money = 300;			//对外击杀获取金钱
	int e_exp;					//对外击杀获取经验
	int m_kill = 0;				//我的击杀
	int m_death = 0;			//我的死亡
	
	double DeadTime = 10;		//死亡时间
	double waitTime = 0;		//等待时间
protected:
	int health;//总生命值
	int nowHealth;//当前生命值
	int attack;//攻击力
	int attackarmor; //物抗
	int powerarmor;//法抗
	int power;//法术强度
	int radium;//攻击半径
	float velocity;//移动速度
	int m_money=300;//我的金钱
	int m_exp;//我的经验值
	int m_level;//我的等级
	int animeIdentifier;//动画标签：1.Bowman，2.Savage，3.Wizard

	bool isAlive=true;			//是否存活
	bool attackingFlag=false;	//是否正在攻击
	bool Moveable = true;		//是否可以移动
	bool isBacking = false;		//是否正在回城

	float atkdelay=1;			//攻击间隔
	float attackingSpeed;		//攻击速度：1s攻击的次数
	float backSpawn = 5;		//回城时间
	Vec2 Position;				//当前位置
	Vec2 Spawn;					//出生点
	Sprite* Charac;				//人物精灵
	Sprite* Blood=Sprite::create("blood.png");		//血条（红）
	Sprite* Bar=Sprite::create("bar.png");			//血条背景（白）
	Sprite* Bullet = Sprite::create("bulletTest.png");//子弹
};


#endif 
	