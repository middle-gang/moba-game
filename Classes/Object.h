#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "cocos2d.h"
#include "Blood.h"
#include "DataDefine.h"
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
	
	const ObjectBase operator +(const EquipmentData equip);//����װ������
	const ObjectBase operator -(const EquipmentData equip);//����װ������

	bool InRange(Vec2 ene);		//�ж�ene�����Ƿ��ڹ�����Χ��
	bool Death();                //�ж������Ƿ�������������true�����false
	bool& isAttacking();		//�ж������Ƿ��ڹ�����ȴ�ڣ����ι���֮��ļ����
	bool isHero();				//�ж������ǲ���Ӣ��
	
	int& getRadium();			//�����õ���ʽ��������Ĺ�����Χ
	int getVelocity();			//��ȡ������ƶ��ٶ�
	virtual int Attack(ObjectBase& ene);	//��������������˺�����������ɱ
	float& AttackPower();				//������ʽ���ع�����
	int& healthPower();				//������ʽ����Ŀǰ����
	int& totalHealth();				//������ʽ����������ֵ

	int ObjectType();

	//void changeTotalHealth(int h);       //�ı�������ֵ
	float AttackSpeed();         //���﹥���ٶ�
	float Power();               //����ǿ��
	int MagicPoint();            //���﷨��ֵ
	float Armor();              //���ﻤ��ֵ
	float MagicDefence();      //ħ��
	int HealthRecover();       //��Ѫ
	int MagicPointRecover();   //����
	float ArmorIgnore();        //����͸
	float MagicDefenseIgnore();//������͸
	float E_Armor();               //��ȡ���ֻ���ֵ
	float E_MagicDenfense();       //��ȡ����ħ��
	int E_Kill();       //��ȡ���ֻ�ɱ��    
	int E_Level();      //��ȡ���ֵȼ���

    void Die();					//������ʱ�����
	void BeAttack(float n);		//������˺���Attack�е��ã�
	void setVelocity(int v);	//�����ٶ�
	void changeVeclocity(int v);   //�ı��ٶ�
	void Move(Vec2 dest);		//�ƶ�����������Ϊ����
	void revive();				//��������
	void setAttackingSpeed(float tms);//���ù����ٶȣ�ÿ�빥���Ĵ�����
	void attachToSprite(Sprite* spr);//��ObjectBase�����ض�����Խ�
	void setSpawnPoint(Vec2 spawn);//���ó�����
	void JudgeAttack(float& jt);	//���������ʱֵ jt ���絽�﹥����������ٴι������ҽ� jt ����
	void setMoveablity(bool mab);	//�����Ƿ�Ϊ���ƶ���������ˮ�������ƶ���
	void initBloodScale();			//��ʼ��Ѫ��
	void setAnimeIdentifier(int i); //���ö�����ǩ
	void HeroInit(Sprite*& spr,Vec2 spawnP); //Ӣ�۵ĳ�ʼ��������İ󶨺�����ֵ��ʼ��
	void JudgeAttackSpeedLevel();		//���ݵ�λ���ù����ٶ�
	void SetAtkSpeedLevel(int n);			//���ù����ٶȵĵȼ�
	void HealthRebound(float delta);				//�ظ�����ֵ
	void MagicRebound(float delta);				//�ظ�����ֵ
	void setArmor(float ar);					//���û���ֵ

	float attackDelay();		//���ع����ӳ�ʱ��
	
	Vec2& getPosition();		//��ȡλ��
	Vec2 SpawnPoint();			//��ȡ������
	Sprite* getSprite();		//��ȡ���ﾫ��
	Sprite* getBullet();		//��ȡ�ӵ����д���ƣ�
	
	ProgressView* BloodView;	//Ѫ��

	int m_death = 0;			//�ҵ�����

	int HeroIdentifier;//Ӣ�۱�ǩ��1.Bowman��2.Savage��3.Wizard
	double DeadTime = 10;		//����ʱ��
	double waitTime = 0;		//�ȴ�ʱ��
	Equipment EquipList;
protected:
	float attack;//������
	float armorIgnore;//���״�͸

	int health;//������ֵ
	int nowHealth;//��ǰ����ֵ

	int healthRecover;//�����ظ�
	bool HomeHPRecover=false;//�ж��Ƿ���Ȫˮ�е������ظ�

	int magicpoint;//����ֵ
	int nowMagicpoint;//��ǰ����ֵ
	int magicpointRecover;//�����ظ�
	bool HomeMPRecover = false;//�ж��Ƿ���Ȫˮ�е������ظ�

	float armor;//����ֵ
	float magicDenfence;//ħ��

	float power;//����ǿ��
	float magicdenfenceIgnore;//������͸


	int radium;//�����뾶

	float velocity;//�ƶ��ٶ�

	//float damageChance=0; //��������

	int equip[6] = { -1,-1,-1,-1,-1,-1 };


	bool isAlive=true;			//�Ƿ���
	bool attackingFlag=false;	//�Ƿ����ڹ���
	bool Moveable = true;		//�Ƿ�����ƶ�

	float atkdelay=1;			//�������
	float atkSpeedLevel=0;		//�����ٶȵĵȼ������ݹ�����ֵ
	float attackingSpeed=0;		//�����ٶȣ�1s�����Ĵ���
	float backSpawn = 5;		//�س�ʱ��
	
	float HPrecoverTimer = 0;	//�����ظ���ʱ�䣬�ں����е�����
	float MPrecoverTimer = 0;	//�����ظ���ʱ�䣬�ں����е�����
	float ExpAndMoneytimer = 0;//��Ǯ�;������Ȼ����

	Vec2 Position;				//��ǰλ��
	Vec2 Spawn;					//������
	Sprite* Charac;				//���ﾫ��
	Sprite* Blood=Sprite::create("blood.png");		//Ѫ�����죩
	Sprite* Bar=Sprite::create("bar.png");			//Ѫ���������ף�
	Sprite* Bullet = Sprite::create("bulletTest.png");//�ӵ�

	//������ֵ���ƣ�������ٶȣ�
	//ÿ���ӹ����������ﵽ����ֵ���ӣ�û�ﵽ��ֵ����
	float HeroAtkSpeedLim[3][11] = {
		{52,55,58,62,66,71,77,84,92,102,115},
		{55,58,62,66,71,77,84,92,102,115.131},
		{55,58,62,66,71,77,84,92,102,115.131}
	};

	//����Ӣ�۵Ĺ�����ֵ
	//�����ٶ������Ľڵ�
	float AtkSpeed[3][11] = {
		{0,2,10,17,28,38,54,70,91,117,154},
		{0,1,9,17,27,38,52,69,90,116,152},
		{0,1,9,17,27,38,52,69,90,116,152}
	};

	//����Ӣ�۵Ļ�����ֵ���ɳ�
	//0����������1�������ɳ�
	//2�������ٶȣ�3�������ٶȳɳ�
	//4������ֵ��5������ֵ�ɳ�
	//6�������ظ���7�������ظ��ɳ�
	//8���￹��9���￹�ɳ�
	//10��ħ����11��ħ���ɳ�
	//12������ֵ��13������ֵ�ɳ�
	//14�������ظ���15�������ظ��ɳ�
	//16�����٣�����ɳ���
	float HeroData[3][17] = {
		{180,16.5,0,1,3182,200,41,2,86,18,50,8.5,440,96,16,1.5,50},
		{164,13,0,1,3622,316,55,3.5,98,21.5,50,8.5,0,0,0,0,60},
		{170,8.5,0,1,3229,185,55,2,86,17,50,8.5,490,109,18,1.5,50},
	};
	//0��Bowman��1��Savage��2��Wizard
	
	//����ֵ���Զ��壬����ϸ���ϣ�
	int Exp[17] = {
		50,75,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475
	};//ÿһ����������Ҫ�ľ���ֵ
};


#endif 
	