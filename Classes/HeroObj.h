#include "Object.h"

class Hero :public ObjectBase {
public:
	const Hero Hero::operator -(const EquipmentData equip);
	const Hero Hero::operator +(const EquipmentData equip);
	void LvUp();								//获取经验值的时候调用，如果升级就改变，不升级不变
	void setHomerecover();                       //设置在家中的回血回蓝量
	void removeHomerecover();                    //离开家取消回血回蓝
	void ExpAndMoneyIncrease(float delta);		//金币和经验的自然增长
	void Buy(int EquipNumber);					//买东西
	void Sale(int locationNum);					//卖东西（装备栏某个位置的）
	void setMoney(int n);						//设置金钱（调试用）
	void BackToSpawn();				//回到出生点
	void Interrupt();				//打断回城
	void JudgeBack(float& time, float del);	//传入参数计时值 time 假如回城时间到就回城并且将 time 归零
	void Kill_reward(ObjectBase& ene);//击杀获得奖励（金钱经验）
	virtual int Attack(ObjectBase& ene);	//攻击函数，造成伤害，动画，击杀
	virtual void BeAttack(float n);		//被造成伤害（Attack中调用）

	float PhysicBloodSuck();    //物理吸血
	float MagicBloodSuck();     //法术吸血
	float WaitLessen();         //冷却缩减

	bool& CheckBacking();

	int m_kill = 0;				//我的击杀
	int m_death = 0;			//我的死亡
private:
	Equipment EquipList;		//装备信息


	float physicBloodSuck = 0;//物理吸血
	float magicBloodSuck = 0;//法术吸血
	float waitLessen = 0;//冷却缩减

	bool isBacking = false;		//是否正在回城

	int equip[6] = { -1,-1,-1,-1,-1,-1 };
};

