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
	float& AttackPower();				//������ʽ���ع�����
	int& healthPower();				//������ʽ����Ŀǰ����
	int& totalHealth();				//������ʽ����������ֵ
	int ObjectType();

	void Die();					//������ʱ�����
	void BeAttack(float n);		//������˺���Attack�е��ã�
	void setVelocity(int v);	//�����ٶ�
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
	void JudgeAttackSpeedLevel();		//���ݵ�λ���ù����ٶ�
	void SetAtkSpeedLevel(int n);			//���ù����ٶȵĵȼ�
	void HealthRebound(float delta);				//�ظ�����ֵ
	void MagicRebound(float delta);				//�ظ�����ֵ
	void setArmor(float ar);					//���û���ֵ
	void LvUp();								//��ȡ����ֵ��ʱ����ã���������͸ı䣬����������
	void setHomerecover();                       //�����ڼ��еĻ�Ѫ������
	void removeHomerecover();                    //�뿪��ȡ����Ѫ����

	float attackDelay();		//���ع����ӳ�ʱ��
	
	Vec2& getPosition();		//��ȡλ��
	Vec2 SpawnPoint();			//��ȡ������
	Sprite* getSprite();		//��ȡ���ﾫ��
	Sprite* getBullet();		//��ȡ�ӵ����д���ƣ�
	
	ProgressView* BloodView;	//Ѫ��

	int e_money = 300;			//�����ɱ��ȡ��Ǯ
	int e_exp;					//�����ɱ��ȡ����
	int m_kill = 0;				//�ҵĻ�ɱ
	int m_death = 0;			//�ҵ�����

	double DeadTime = 10;		//����ʱ��
	double waitTime = 0;		//�ȴ�ʱ��
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

	int m_money=0;//�ҵĽ�Ǯ
	int m_exp;//�ҵľ���ֵ
	int MyLevel=1;//�ҵĵȼ�
	int HeroIdentifier;//Ӣ�۱�ǩ��1.Bowman��2.Savage��3.Wizard

	bool isAlive=true;			//�Ƿ���
	bool attackingFlag=false;	//�Ƿ����ڹ���
	bool Moveable = true;		//�Ƿ�����ƶ�
	bool isBacking = false;		//�Ƿ����ڻس�

	float atkdelay=1;			//�������
	float atkSpeedLevel=0;		//�����ٶȵĵȼ������ݹ�����ֵ
	float attackingSpeed=0;		//�����ٶȣ�1s�����Ĵ���
	float backSpawn = 5;		//�س�ʱ��
	
	float HPrecoverTimer = 0;	//�����ظ���ʱ�䣬�ں����е�����
	float MPrecoverTimer = 0;	//�����ظ���ʱ�䣬�ں����е�����

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
		{180,16.5,0,1,3182,200,41,2,86,18,50,8.5,440,96,16,1.5,360},
		{164,13,0,1,3622,316,55,3.5,98,21.5,50,8.5,0,0,0,0,390},
		{170,8.5,0,1,3229,185,55,2,86,17,50,8.5,490,109,18,1.5,360},
	};
	//0��Bowman��1��Savage��2��Wizard
	
	//����ֵ���Զ��壬����ϸ���ϣ�
	int Exp[17] = {
		50,75,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475
	};//ÿһ����������Ҫ�ľ���ֵ
};


#endif 
	