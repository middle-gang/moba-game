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
	
	bool InRange(Vec2 ene);		//�ж�ene�����Ƿ��ڹ�����Χ��
	bool Death();                //�ж������Ƿ�������������true�����false
	bool& isAttacking();		//�ж������Ƿ��ڹ�����ȴ�ڣ����ι���֮��ļ����
	bool& CheckBacking();		//�ж������Ƿ��ڻس�
	
	int& getRadium();			//�����õ���ʽ��������Ĺ�����Χ
	int getVelocity();			//��ȡ������ƶ��ٶ�
	int Money();				//����Ľ�Ǯ
	int Attack(ObjectBase& ene);	//��������������˺�����������ɱ
	int& AttackPower();				//������ʽ���ع�����
	int& healthPower();				//������ʽ����Ŀǰ����
	int& totalHealth();				//������ʽ����������ֵ
	void changeTotalHealth(int h);       //�ı�������ֵ

	void Die();					//������ʱ�����
	void BeAttack(int n);		//������˺���Attack�е��ã�
	void setVelocity(int v);	//�����ٶ�
	void changeVeclocity(int v);   //�ı��ٶ�
	void Move(Vec2 dest);		//�ƶ�����������Ϊ����
	void revive();				//��������
	void setAttackingSpeed(float tms);//���ù����ٶȣ�ÿ�빥���Ĵ�����
	void attachToSprite(Sprite* spr);//��ObjectBase�����ض�����Խ�
	void Kill_reward(ObjectBase& ene);//��ɱ��ý�������Ǯ���飩
	void setSpawnPoint(Vec2 spawn);//���ó�����
	void JudgeAttack(float& jt);	//���������ʱֵ jt ���絽�﹥����������ٴι������ҽ� jt ����
	void setMoveablity(bool mab);	//�����Ƿ�Ϊ���ƶ���������ˮ�������ƶ���
	void initBloodScale();			//��ʼ��Ѫ��
	void setAnimeIdentifier(int i); //���ö�����ǩ
	void HeroInit(Sprite*& spr,Vec2 spawnP); //Ӣ�۵ĳ�ʼ��������İ󶨺�����ֵ��ʼ��
	void BackToSpawn();				//�ص�������
	void Interrupt();				//��ϻس�
	void JudgeBack(float& time, float del);	//���������ʱֵ time ����س�ʱ�䵽�ͻسǲ��ҽ� time ����

	float attackDelay();		//���ع����ӳ�ʱ��
	
	Vec2& getPosition();		//��ȡλ��
	Sprite* getSprite();		//��ȡ���ﾫ��
	Sprite* getBullet();		//��ȡ�ӵ����д���ƣ�
	
	ProgressView* BloodView;	//Ѫ��

    int e_tower = 0;            //�Ƶ��Է�����
	int e_money = 300;			//�����ɱ��ȡ��Ǯ
	int e_exp;					//�����ɱ��ȡ����
	int m_kill = 0;				//�ҵĻ�ɱ
	int m_death = 0;			//�ҵ�����
	
	double DeadTime = 10;		//����ʱ��
	double waitTime = 0;		//�ȴ�ʱ��
protected:
	int health;//������ֵ
	int nowHealth;//��ǰ����ֵ
	int attack;//������
	int attackarmor; //�￹
	int powerarmor;//����
	int power;//����ǿ��
	int radium;//�����뾶
	float velocity;//�ƶ��ٶ�
	int m_money=300;//�ҵĽ�Ǯ
	int m_exp;//�ҵľ���ֵ
	int m_level;//�ҵĵȼ�
	int animeIdentifier;//������ǩ��1.Bowman��2.Savage��3.Wizard

	bool isAlive=true;			//�Ƿ���
	bool attackingFlag=false;	//�Ƿ����ڹ���
	bool Moveable = true;		//�Ƿ�����ƶ�
	bool isBacking = false;		//�Ƿ����ڻس�

	float atkdelay=1;			//�������
	float attackingSpeed;		//�����ٶȣ�1s�����Ĵ���
	float backSpawn = 5;		//�س�ʱ��
	Vec2 Position;				//��ǰλ��
	Vec2 Spawn;					//������
	Sprite* Charac;				//���ﾫ��
	Sprite* Blood=Sprite::create("blood.png");		//Ѫ�����죩
	Sprite* Bar=Sprite::create("bar.png");			//Ѫ���������ף�
	Sprite* Bullet = Sprite::create("bulletTest.png");//�ӵ�
};


#endif 
	