#include "Object.h"

class HeroObj :public ObjectBase {
public:
	const HeroObj HeroObj::operator -(const EquipmentData equip);
	const HeroObj HeroObj::operator +(const EquipmentData equip);
	void LvUp();								//��ȡ����ֵ��ʱ����ã���������͸ı䣬����������
	void setHomerecover();                       //�����ڼ��еĻ�Ѫ������
	void removeHomerecover();                    //�뿪��ȡ����Ѫ����
	void ExpAndMoneyIncrease(float delta);		//��Һ;������Ȼ����
	void Buy(int EquipNumber);					//����
	void Sale(int locationNum);					//��������װ����ĳ��λ�õģ�
	void setMoney(int n);						//���ý�Ǯ�������ã�
	void BackToSpawn();				//�ص�������
	void Interrupt();				//��ϻس�
	void JudgeBack(float& time, float del);	//���������ʱֵ time ����س�ʱ�䵽�ͻسǲ��ҽ� time ����
	void Kill_reward(ObjectBase& ene);//��ɱ��ý�������Ǯ���飩
	virtual int Attack(ObjectBase& ene);	//��������������˺�����������ɱ
	virtual void BeAttack(float n);		//������˺���Attack�е��ã�
	virtual void Die();

	float PhysicBloodSuck();    //������Ѫ
	float MagicBloodSuck();     //������Ѫ
	float WaitLessen();         //��ȴ����

	bool& CheckBacking();
	bool QIsUsed();		//Q�����Ƿ�ʹ��
	bool WIsUsed();		//W�����Ƿ�ʹ��
	bool EIsUsed();		//E�����Ƿ�ʹ��

	void Ability1st();
	void Ability2st();
	void Ability3st();

	void Qjudge(float delta);
	void Wjudge(float delta);
	void Ejudge(float delta);

	int Level();
	int tMoney();
	int Money();

	bool EBoundJudge = false;
	bool EActivate = false;
	HeroObj* Etarget;

	bool WBoundJudge = false;
	bool WActivate = false;
	std::vector<ObjectBase> Wtarget;

	bool QBoundJudge = false;
	bool QActivate = false;
	std::vector<ObjectBase> Qtarget;

	int m_kill = 0;				//�ҵĻ�ɱ
	int m_death = 0;			//�ҵ�����

	int m_money = 0;//�ҵĽ�Ǯ
	int t_money = 0;//�ܻ�ý�Ǯ��
	int m_exp;//�ҵľ���ֵ
	int MyLevel = 1;//�ҵĵȼ�


	int equip[6] = { -1,-1,-1,-1,-1,-1 };
private:

	Equipment EquipList;		//װ����Ϣ

	float physicBloodSuck = 0;//������Ѫ
	float magicBloodSuck = 0;//������Ѫ
	float waitLessen = 0;//��ȴ����

	float Qtimer = 0;		//Q���ܼ�ʱ��
	float Wtimer = 0;		//W���ܼ�ʱ��
	float Etimer = 0;		//E���ܼ�ʱ��

	bool Qflag = false;		//Q����״̬
	bool Wflag = false;		//W����״̬
	bool Eflag = false;		//E����״̬

	bool Qrecover = false;
	bool Wrecover = false;
	bool Erecover = false;

	bool attackStrength = false;	//�Ƿ�����չ�ǿ��

	bool isBacking = false;		//�Ƿ����ڻس�

//	int equip[6] = { -1,-1,-1,-1,-1,-1 };
};

