#ifndef __OBJECT_H__
#define __OBJECT_H__


#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { ClassId = inCode }; \
virtual uint32_t GetClassId() const { return ClassId; } \
static ObjectBase* CreateInstance() { return static_cast< ObjectBase* >( new inClass() ); } \

#include "cocos2d.h"
#include "Blood.h"
#include "DataDefine.h"
#include "MoreauShared.h"
using namespace cocos2d;

class ObjectBase
{
public:

    CLASS_IDENTIFICATION( 'OBJB', ObjectBase )                       //类标志符
    
    ObjectBase()
    {
    }
    ObjectBase(int i,int j,int k,Vec2 pos,std::string str,int t){
        health = i;
        attack = j;
        radium = k;
        Position = pos;
        Charac = Sprite::create(str);
        mNetworkId = t;
//        mIndexInWorld = s;
    }
    
/*
    enum{
        kClassId = 'OBJB'
    };
    virtual uint32_t GetClassId() const {return kClassId;}
    static ObjectBase* CreateInstance(){
        return new ObjectBase();
    }
*/
    
    int GetNetworkId() const
    {
        return mNetworkId;
    }
    void SetNetworkId( int inNetworkId )
    {
        //this doesn't put you in the map or remove you from it
        mNetworkId = inNetworkId;
    }                                                               //网络标志符
    

/*
    void SetIndexInWorld( int inIndex )
    {
        mIndexInWorld = inIndex;
    }
    int GetIndexInWorld() const
    {
        return mIndexInWorld;
    }
*/
    
    virtual uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
    {
        ( void ) inOutputStream;
        ( void ) inDirtyState;
        return 0;
    }
    virtual void Read( InputMemoryBitStream& inInputStream )
    {
        ( void ) inInputStream;
    }                                                                 //读取写⼊比特流函数
    
    
    const ObjectBase operator +(const EquipmentData equip) {
        health += equip.health;
        magicpoint += equip.magicpoint;
        healthRecover+=equip.healthRecover;
        magicpointRecover += equip.magicpointRecover;
        attack += equip.attack;
        power += equip.power;
        
        armor+=equip.armor;
        magicDenfence+=equip.magicDenfence;
        armorIgnore+=equip.armorIgnore;
        magicdenfenceIgnore+=equip.armorIgnore;
        physicBloodSuck+=equip.physicBloodSuck;
        magicBloodSuck+=equip.magicBloodSuck;
        waitLessen+=equip.waitLessen;
        
        velocity+=(equip.velocity*velocity);
        attackingSpeed+=attackingSpeed;
        JudgeAttackSpeedLevel();
        return *this;
    }
    
    const ObjectBase operator -(const EquipmentData equip) {
        health -= equip.health;
        magicpoint -= equip.magicpoint;
        healthRecover -= equip.healthRecover;
        magicpointRecover -= equip.magicpointRecover;
        attack -= equip.attack;
        power -= equip.power;
        
        armor -= equip.armor;
        magicDenfence -= equip.magicDenfence;
        armorIgnore -= equip.armorIgnore;
        magicdenfenceIgnore -= equip.armorIgnore;
        physicBloodSuck -= equip.physicBloodSuck;
        magicBloodSuck -= equip.magicBloodSuck;
        waitLessen -= equip.waitLessen;
        
        velocity -= (equip.velocity*velocity);//??
        attackingSpeed -= attackingSpeed;
        JudgeAttackSpeedLevel();
        return *this;
    }
    
    bool InRange(Vec2 ene);        //判断ene对象是否在攻击范围内
    bool Death();                //判断人物是否死亡。死亡：true，存活false
    bool& isAttacking();        //判断人物是否处于攻击冷却期（两次攻击之间的间隔）
    bool& CheckBacking();        //判断人物是否在回城
    
    int& getRadium();            //以引用的形式返回人物的攻击范围
    int getVelocity();            //获取人物的移动速度
    int Money();                //人物的金钱
    int tMoney();               //人物总获得金钱
    int Level();                //人物等级
    int Attack(ObjectBase& ene);    //攻击函数，造成伤害，动画，击杀
    float& AttackPower();                //引用形式返回攻击力
    int& healthPower();                //引用形式返回目前生命
    int& totalHealth();                //引用形式返回总生命值
    
    int ObjectType();
    
    //void changeTotalHealth(int h);       //改变总生命值
    float AttackSpeed();         //人物攻击速度
    float Power();               //法术强度
    int MagicPoint();            //人物法力值
    float Armor();              //人物护甲值
    float MagicDefence();      //魔抗
    int HealthRecover();       //回血
    int MagicPointRecover();   //回蓝
    float ArmorIgnore();        //物理穿透
    float MagicDefenseIgnore();//法术穿透
    float PhysicBloodSuck();    //物理吸血
    float MagicBloodSuck();     //法术吸血
    float WaitLessen();         //冷却缩减
    float E_Armor();               //获取对手护甲值
    float E_MagicDenfense();       //获取对手魔抗
    int E_Kill();       //获取对手击杀数
    int E_Level();      //获取对手等级数
    
    void Die();                    //死亡的时候调用
    void BeAttack(float n);        //被造成伤害（Attack中调用）
    void setVelocity(int v);    //设置速度
    void changeVeclocity(int v);   //改变速度
    void Move(Vec2 dest);        //移动函数，参数为坐标
    void revive();                //复活到复活点
    void setAttackingSpeed(float tms);//设置攻击速度（每秒攻击的次数）
    void attachToSprite(Sprite* spr);//把ObjectBase类与特定对象对接
    void Kill_reward(ObjectBase& ene);//击杀获得奖励（金钱经验）
    void setSpawnPoint(Vec2 spawn);//设置出生点
    void JudgeAttack(float& jt);    //传入参数计时值 jt 假如到达攻击间隔可以再次攻击并且将 jt 归零
    void setMoveablity(bool mab);    //设置是否为可移动对象（塔和水晶不可移动）
    void initBloodScale();            //初始化血条
    void setAnimeIdentifier(int i); //设置动画标签
    void HeroInit(Sprite*& spr,Vec2 spawnP); //英雄的初始化，精灵的绑定和属性值初始化
    void BackToSpawn();                //回到出生点
    void Interrupt();                //打断回城
    void JudgeBack(float& time, float del);    //传入参数计时值 time 假如回城时间到就回城并且将 time 归零
    void JudgeAttackSpeedLevel();        //根据档位设置攻击速度
    void SetAtkSpeedLevel(int n);            //设置攻击速度的等级
    void HealthRebound(float delta);                //回复生命值
    void MagicRebound(float delta);                //回复法力值
    void setArmor(float ar);                    //设置护甲值
    void LvUp();                                //获取经验值的时候调用，如果升级就改变，不升级不变
    void setHomerecover();                       //设置在家中的回血回蓝量
    void removeHomerecover();                    //离开家取消回血回蓝
    void ExpAndMoneyIncrease(float delta);
    void Buy(int EquipNumber);
    void Sale(int locationNum);
    void setMoney(int n);
    
    float attackDelay();        //返回攻击延迟时间
    
    Vec2& getPosition();        //获取位置
    Vec2 SpawnPoint();            //获取出生点
    Sprite* getSprite();        //获取人物精灵
    Sprite* getBullet();        //获取子弹（有待设计）
    
    ProgressView* BloodView;    //血条
    
    void Read(InputMemoryStream& stream) const;              //封装好的读函数
    void Write(OutputMemoryStream& stream);            //封装好的写函数
    
    int m_kill = 0;                //我的击杀
    int m_death = 0;            //我的死亡
    
    double DeadTime = 10;        //死亡时间
    double waitTime = 0;        //等待时间
    Equipment EquipList;
    
    
protected:
    
//    int mIndexInWorld;
    int mNetworkId;
    
    float attack;//攻击力
    float armorIgnore;//护甲穿透
    
    int health;//总生命值
    int nowHealth;//当前生命值
    
    int healthRecover;//生命回复
    bool HomeHPRecover=false;//判断是否在泉水中的生命回复
    
    int magicpoint;//法力值
    int nowMagicpoint;//当前法力值
    int magicpointRecover;//法力回复
    bool HomeMPRecover = false;//判断是否在泉水中的生命回复
    
    float armor;//护甲值
    float magicDenfence;//魔抗
    
    float power;//法术强度
    float magicdenfenceIgnore;//法术穿透
    
    float physicBloodSuck=0;//物理吸血
    float magicBloodSuck=0;//法术吸血
    float waitLessen = 0;//冷却缩减
    
    int radium;//攻击半径
    
    float velocity;//移动速度
    
    //float damageChance=0; //暴击概率
    
    int equip[6] = { -1,-1,-1,-1,-1,-1 };
    
    int m_money=0;//我的金钱
    int t_money = 0;///总获得金钱数
    int m_exp;//我的经验值
    int MyLevel=1;//我的等级
    int HeroIdentifier;//英雄标签：1.Bowman，2.Savage，3.Wizard
    
    bool isAlive=true;            //是否存活
    bool attackingFlag=false;    //是否正在攻击
    bool Moveable = true;        //是否可以移动
    bool isBacking = false;        //是否正在回城
    
    float atkdelay=1;            //攻击间隔
    float atkSpeedLevel=0;        //攻击速度的等级，根据攻速阈值
    float attackingSpeed=0;        //攻击速度：1s攻击的次数
    float backSpawn = 5;        //回城时间
    
    float HPrecoverTimer = 0;    //生命回复的时间，在函数中调用用
    float MPrecoverTimer = 0;    //法力回复的时间，在函数中调用用
    float ExpAndMoneytimer = 0;//金钱和经验的自然增长
    
    Vec2 Position;                //当前位置
    Vec2 Spawn;                    //出生点
    Sprite* Charac;                //人物精灵
    Sprite* Blood=Sprite::create("blood.png");        //血条（红）
    Sprite* Bar=Sprite::create("bar.png");            //血条背景（白）
    Sprite* Bullet = Sprite::create("bulletTest.png");//子弹
    
    //攻速阈值机制（详情见百度）
    //每分钟攻击次数，达到了阈值增加，没达到阈值不变
    float HeroAtkSpeedLim[3][11] = {
        {52,55,58,62,66,71,77,84,92,102,115},
        {55,58,62,66,71,77,84,92,102,115.131},
        {55,58,62,66,71,77,84,92,102,115.131}
    };
    
    //三个英雄的攻击阈值
    //攻击速度提升的节点
    float AtkSpeed[3][11] = {
        {0,2,10,17,28,38,54,70,91,117,154},
        {0,1,9,17,27,38,52,69,90,116,152},
        {0,1,9,17,27,38,52,69,90,116,152}
    };
    
    //三个英雄的基础数值及成长
    //0：攻击力，1：攻击成长
    //2：攻击速度，3：攻击速度成长
    //4：生命值，5：生命值成长
    //6：生命回复，7：生命回复成长
    //8：物抗，9：物抗成长
    //10：魔抗，11：魔抗成长
    //12：法力值，13：法力值成长
    //14：法力回复，15：法力回复成长
    //16：移速（不会成长）
    float HeroData[3][17] = {
        {180,16.5,0,1,3182,200,41,2,86,18,50,8.5,440,96,16,1.5,36},
        {164,13,0,1,3622,316,55,3.5,98,21.5,50,8.5,0,0,0,0,39},
        {170,8.5,0,1,3229,185,55,2,86,17,50,8.5,490,109,18,1.5,36},
    };
    //0：Bowman，1：Savage，2：Wizard
    
    //经验值（自定义，无详细资料）
    int Exp[17] = {
        50,75,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475
    };//每一次升级所需要的经验值
};


typedef shared_ptr< GameObject > GameObjectPtr;

#endif
