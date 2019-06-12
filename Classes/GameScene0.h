#ifndef __GAMESCENE0_H__
#define __GAMESCENE0_H__

#include "cocos2d.h"
#include"GameScene2.h"
#include"HelloWorldScene.h"
#include"GlobalVal.h"
#include"DataDefine.h"


using namespace cocos2d;

class GameScene0 : public cocos2d::Layer
{
private:
	GameScene2 *m_pGameScene2;
	//HUDLayer *m_pHUDLayer;

private:
	////属性
	int m_kill;   //击杀对手数
	int m_death;   //死亡数
	int e_kill;    //对手击杀数
	int e_death;   //对手死亡数
	//int m_assist;  //助攻数
	//int m_monster;  //击杀野怪数
	int m_tower;///推塔数
	int m_money;//目前金钱
	int t_money;//获得金钱
	int m_level; //等级
	int e_level;//对手等级

	float m_attack;//攻击力
	float m_power;//法术强度
	int m_health;//总生命值
	int magicpoint;//法力值
	float armor;//护甲值
	float magicDenfence;//魔抗
	float attackingSpeed;  //攻击速度
	float waitLessen;//冷却缩减
	float velocity;//移动速度
	int healthRecover;//生命回复
	int magicpointRecover;//法力回复 
	float armorIgnore;//护甲穿透
	float magicdenfenceIgnore;//法术穿透
	float physicBloodSuck;//物理吸血
	float magicBloodSuck;//法术吸血

	//////装备
	//EquipmentData s_Equip[8][30];
	cocos2d::MenuItemImage*Equipment[8][30];

private:
	///时间
	char m_Textbuffer[999];
	int time_min;
	int time_sec;
	float time;
	int number;

	cocos2d::Label *m_pTime_minText;
	cocos2d::Label *m_pTime_secText;

	////技能冷却
	int m_SkillWait[6];
	int SkillWait[6];

	bool m_SkillUp[6];

	float m_pass[6];

	cocos2d::Label *m_pSkillText[6];

private:
	///////////////数值显示1
	cocos2d::Label *m_pKillText[4];//左上
	cocos2d::Label *e_pKillText;

	cocos2d::Label *m_pDeathText;
	cocos2d::Label *m_pDeath2Text;///死亡标签

	cocos2d::Label *m_pLevelText;//等级

	cocos2d::Label *m_pMoneyText;
	cocos2d::Label *m_pMoney2Text;

	cocos2d::Label *t_pMoneyText;
	cocos2d::Label *t_pMoney2Text;

	cocos2d::Label *m_pAttri1Text[6];

	////////////////数值显示2（属性面板）
	cocos2d::Label  *m_pAttri2Text[17];
	//cocos2d::Label *m_pAttackText;     //物理攻击
	//cocos2d::Label *m_pPowerText;      //法术攻击
	//cocos2d::Label *m_pHelthText;      //最大生命
	//cocos2d::Label *m_pMagicPointText;    //最大法力
	//cocos2d::Label *m_pArmorText;         //物理防御
	//cocos2d::Label *m_pMagicDefenseText;      //法术防御
	//cocos2d::Label *m_pAttackingSpeendText;    //攻击速度
	//cocos2d::Label *m_pWaitLessenText;          //冷却缩减
	//cocos2d::Label *m_pDamageChanceText;        //暴击几率
	//cocos2d::Label *m_pVelocityText;            //移动速度
	//cocos2d::Label *m_pHealthRecoverText;       //每5秒回血
	//cocos2d::Label *m_pMagicPointRecoverText;     //每5秒回蓝
	//cocos2d::Label *m_pArmorIgnoreText;          //物理穿透
	//cocos2d::Label *m_pMagicDefenceText;         //法术穿透
	//cocos2d::Label *m_pPhysicBloodSuckText;      //物理吸血
	//cocos2d::Label *m_pMagicBloodSuckText;       //法术吸血


	//属性面板1背景及按钮(对战）
	bool AttriIsOpen;
	cocos2d::Sprite *m_AttriBack1;
	cocos2d::Sprite *m_AttriBack2;
	cocos2d::MenuItemImage *m_pOpAttriMii;
	cocos2d::MenuItemImage  *m_pHeroAttriMii;
	cocos2d::MenuItemImage *m_pCloseAttri;
	cocos2d::Menu *m_pAttriMenu;

	///////////////属性面板2背景及按钮（个人详细）
	cocos2d::Sprite *m_AttriB1;
	cocos2d::Sprite *m_AttriB2;
	cocos2d::MenuItemImage *m_button1;
	cocos2d::MenuItemImage *m_button2;
	cocos2d::MenuItemImage *m_closebutton;
	cocos2d::Menu *m_AttriMenu;

	////////////商店面板及按钮
	bool ShopIsOpen;
	cocos2d::Sprite *m_ShopBack;
	cocos2d::MenuItemImage *m_pRecomMii;
	cocos2d::MenuItemImage *m_pAttackMii;
	cocos2d::MenuItemImage *m_pMagicMii;
	cocos2d::MenuItemImage *m_pDefenseMii;
	cocos2d::MenuItemImage *m_pMoveMii;
	cocos2d::MenuItemImage *m_pBattleMii;
	cocos2d::MenuItemImage *m_pAssistMii;
	cocos2d::MenuItemImage *m_pDownMii;///记录按下去的
	cocos2d::MenuItemImage *m_pCloseShop;
	cocos2d::Menu *m_pShopMenu;

	//商店菜单
	cocos2d::Menu *m_pDownMenu;//记录按下去的；
	cocos2d::Sprite *m_pDownBac;

	cocos2d::Sprite *m_pBac[8];

	cocos2d::Menu *m_pRecommandMenu;
	cocos2d::Menu *m_pAttackMenu;
	cocos2d::Menu *m_pMagicMenu;
	cocos2d::Menu *m_pDefenseMenu;
	cocos2d::Menu *m_pMoveMenu;
	cocos2d::Menu *m_pBattleMenu;
	cocos2d::Menu *m_pAssistMenu;

	//询问退出界面及按钮
	bool ExitIsOpen;
	cocos2d::Sprite *m_ExitBack;
	cocos2d::MenuItemImage *m_pYesMii;
	cocos2d::MenuItemImage *m_pNoMii;
	cocos2d::Menu *m_pExitMenu;

	bool m_IsPopDialog;
	float m_DialogPopTime;

	//创建蒙版
	cocos2d::Sprite *m_pMaskImage;

	//显示按钮：属性，商店，退出
	cocos2d::Menu *m_pMenu;

	//技能面板
	cocos2d::MenuItemImage *pAttackMii;
	cocos2d::MenuItemImage*pSkillMii[6];

	cocos2d::Menu *m_pSkillMenu;


public:
	//属性面板函数
	void transToOp(cocos2d::Ref* pSender);
	void transToHero(cocos2d::Ref* pSender);
	void closeAttri(cocos2d::Ref* pSender);

	//属性面板2函数
	void openAttri2(cocos2d::Ref* pSender);
	void transTo1(cocos2d::Ref* pSender);
	void transTo2(cocos2d::Ref* pSender);
	void closeAttri2(cocos2d::Ref* pSender);

	///////////////////商店面板函数
	void openShop(cocos2d::Ref* pSender);
	void closeShop(cocos2d::Ref* pSender);

	void RecommendMenu(cocos2d::Ref* pSender);
	void AttackMenu(cocos2d::Ref* pSender);
	void MagicMenu(cocos2d::Ref* pSender);
	void DefenseMenu(cocos2d::Ref* pSender);
	void MoveMenu(cocos2d::Ref* pSender);
	void BattleMenu(cocos2d::Ref* pSender);
	void AssistMenu(cocos2d::Ref* pSender);

	//物品操作函数
	void attack0(cocos2d::Ref* pSender);
	void attack1(cocos2d::Ref* pSender);
	void attack2(cocos2d::Ref* pSender);
	void attack3(cocos2d::Ref* pSender);
	void attack4(cocos2d::Ref* pSender);
	void attack5(cocos2d::Ref* pSender);
	void attack6(cocos2d::Ref* pSender);
	void attack7(cocos2d::Ref* pSender);
	void attack8(cocos2d::Ref* pSender);
	void attack9(cocos2d::Ref* pSender);
	void attack10(cocos2d::Ref* pSender);
	void attack11(cocos2d::Ref* pSender);
	void attack12(cocos2d::Ref* pSender);
	void attack13(cocos2d::Ref* pSender);
	void attack14(cocos2d::Ref* pSender);
	void attack15(cocos2d::Ref* pSender);

	void magic0(cocos2d::Ref* pSender);
	void magic1(cocos2d::Ref* pSender);
	void magic2(cocos2d::Ref* pSender);
	void magic3(cocos2d::Ref* pSender);
	void magic4(cocos2d::Ref* pSender);
	void magic5(cocos2d::Ref* pSender);
	void magic6(cocos2d::Ref* pSender);
	void magic7(cocos2d::Ref* pSender);
	void magic8(cocos2d::Ref* pSender);
	void magic9(cocos2d::Ref* pSender);
	void magic10(cocos2d::Ref* pSender);
	void magic11(cocos2d::Ref* pSender);
	void magic12(cocos2d::Ref* pSender);
	void magic13(cocos2d::Ref* pSender);
	void magic14(cocos2d::Ref* pSender);
	void magic15(cocos2d::Ref* pSender);

	void defense0(cocos2d::Ref* pSender);
	void defense1(cocos2d::Ref* pSender);
	void defense2(cocos2d::Ref* pSender);
	void defense3(cocos2d::Ref* pSender);
	void defense4(cocos2d::Ref* pSender);
	void defense5(cocos2d::Ref* pSender);
	void defense6(cocos2d::Ref* pSender);
	void defense7(cocos2d::Ref* pSender);
	void defense8(cocos2d::Ref* pSender);
	void defense9(cocos2d::Ref* pSender);
	void defense10(cocos2d::Ref* pSender);
	void defense11(cocos2d::Ref* pSender);
	void defense12(cocos2d::Ref* pSender);
	void defense13(cocos2d::Ref* pSender);
	void defense14(cocos2d::Ref* pSender);
	void defense15(cocos2d::Ref* pSender);

	void move0(cocos2d::Ref* pSender);
	void move1(cocos2d::Ref* pSender);
	void move2(cocos2d::Ref* pSender);
	void move3(cocos2d::Ref* pSender);
	void move4(cocos2d::Ref* pSender);
	void move5(cocos2d::Ref* pSender);
	void move6(cocos2d::Ref* pSender);

	void battle0(cocos2d::Ref* pSender);
	void battle1(cocos2d::Ref* pSender);
	void battle2(cocos2d::Ref* pSender);
	void battle3(cocos2d::Ref* pSender);
	void battle4(cocos2d::Ref* pSender);
	void battle5(cocos2d::Ref* pSender);
	void battle6(cocos2d::Ref* pSender);

	void assist0(cocos2d::Ref* pSender);
	void assist1(cocos2d::Ref* pSender);
	void assist2(cocos2d::Ref* pSender);
	void assist3(cocos2d::Ref* pSender);
	void assist4(cocos2d::Ref* pSender);
	void assist5(cocos2d::Ref* pSender);
	void assist6(cocos2d::Ref* pSender);
	void assist7(cocos2d::Ref* pSender);
	void assist8(cocos2d::Ref* pSender);


	//退出界面函数
	void openExit(cocos2d::Ref* pSender);
	void menuYesCallback(cocos2d::Ref* pSender);
	void menuNoCallback(cocos2d::Ref* pSender);
	///技能函数
	void Skill1(cocos2d::Ref* pSender);
	void Skill2(cocos2d::Ref* pSender);
	void Skill3(cocos2d::Ref* pSender);

	void attack(cocos2d::Ref* pSender);
	void recover(cocos2d::Ref* pSender);
	void cure(cocos2d::Ref* pSender);


public:
	static cocos2d::Scene* createScene();

	virtual void GameScene0::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual bool init();

	virtual void update(float delta);


	CREATE_FUNC(GameScene0);
};

#endif 
