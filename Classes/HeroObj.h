#include "Object.h"

class Hero :public ObjectBase {
public:
	const Hero Hero::operator -(const EquipmentData equip);
	const Hero Hero::operator +(const EquipmentData equip);
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

	float PhysicBloodSuck();    //������Ѫ
	float MagicBloodSuck();     //������Ѫ
	float WaitLessen();         //��ȴ����

	bool& CheckBacking();

	int m_kill = 0;				//�ҵĻ�ɱ
	int m_death = 0;			//�ҵ�����
private:
	Equipment EquipList;		//װ����Ϣ


	float physicBloodSuck = 0;//������Ѫ
	float magicBloodSuck = 0;//������Ѫ
	float waitLessen = 0;//��ȴ����

	bool isBacking = false;		//�Ƿ����ڻس�

	int equip[6] = { -1,-1,-1,-1,-1,-1 };
};

