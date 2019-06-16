#include "Object.h"
#include "cocos2d.h"

class HeroObj :public ObjectBase {
public:
    const HeroObj HeroObj::operator -(const EquipmentData equip);
    const HeroObj HeroObj::operator +(const EquipmentData equip);
    void LvUp();                                //获取经验值的时候调用，如果升级就改变，不升级不变
    void setHomerecover();                       //设置在家中的回血回蓝量
    void removeHomerecover();                    //离开家取消回血回蓝
    void ExpAndMoneyIncrease(float delta);        //金币和经验的自然增长
    void Buy(int EquipNumber);                    //买东西
	void HeroObj::Sale(int locNumber, int Equipnumber) ;                    //卖东西（装备栏某个位置的）
    void setMoney(int n);                        //设置金钱（调试用）
    void BackToSpawn();                //回到出生点
    void Interrupt();                //打断回城
    void JudgeBack(float& time, float del);    //传入参数计时值 time 假如回城时间到就回城并且将 time 归零
    void Kill_reward(ObjectBase& ene);//击杀获得奖励（金钱经验）
    virtual int Attack(ObjectBase& ene);    //攻击函数，造成伤害，动画，击杀
    // virtual void BeAttack(float n);        //被造成伤害（Attack中调用）
    //virtual void Die();
    
    float PhysicBloodSuck();    //物理吸血
    float MagicBloodSuck();     //法术吸血
    float WaitLessen();         //冷却缩减
    
    bool& CheckBacking();
    bool QIsUsed();        //Q技能是否使用
    bool WIsUsed();        //W技能是否使用
    bool EIsUsed();        //E技能是否使用
    
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
    
    int m_kill = 0;                //我的击杀
    //    int m_death = 0;            //我的死亡
    
    int m_money = 0;//我的金钱
    int t_money = 0;//总获得金钱数
    int m_exp;//我的经验值
    int MyLevel = 1;//我的等级
    
    
    int equip[6] = { -1,-1,-1,-1,-1,-1 };
private:
    
    Equipment EquipList;        //装备信息
    
    float physicBloodSuck = 0;//物理吸血
    float magicBloodSuck = 0;//法术吸血
    float waitLessen = 0;//冷却缩减
    
    float Qtimer = 0;        //Q技能计时器
    float Wtimer = 0;        //W技能计时器
    float Etimer = 0;        //E技能计时器
    
    bool Qflag = false;        //Q技能状态
    bool Wflag = false;        //W技能状态
    bool Eflag = false;        //E技能状态
    
    bool Qrecover = false;
    bool Wrecover = false;
    bool Erecover = false;
    
    bool attackStrength = false;    //是否产生普攻强化
    
    bool isBacking = false;        //是否正在回城
    
    //    int equip[6] = { -1,-1,-1,-1,-1,-1 };
};
