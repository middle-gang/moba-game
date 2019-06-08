#ifndef __GAMESCENE0_H__
#define __GAMESCENE0_H__

#include "cocos2d.h"
#include"GameScene2.h"
#include"HelloWorldScene.h"
#include"GlobalVal.h"
//#include"HUDLayer.h"


using namespace cocos2d;

class GameScene0 : public cocos2d::Layer
{
public:

private:
	GameScene2 *m_pGameScene2;
	//HUDLayer *m_pHUDLayer;


public:
	////属性
	int m_kill;   //击杀对手数
	int m_death;   //死亡数
	//int m_assist;  //助攻数
	//int m_monster;  //击杀野怪数
	int m_tower;
	int m_money;
	int m_money2;//目前金钱
	int t_money;//获得金钱
	int m_Score;
	int m_Level;

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
	int m_Skill1Wait;
	int m_Skill2Wait;
	int m_Skill3Wait;
	int m_Skill4Wait;
	int m_Skill5Wait;

	bool m_Skill1Up;
	bool m_Skill2Up;
	bool m_Skill3Up;
	bool m_Skill4Up;
	bool m_Skill5Up;

	float m_pass1;
	float m_pass2;
	float m_pass3;
	float m_pass4;
	float m_pass5;

	cocos2d::Label *m_pSkill1Text;
	cocos2d::Label *m_pSkill2Text;
	cocos2d::Label *m_pSkill3Text;
	cocos2d::Label *m_pSkill4Text;
	cocos2d::Label *m_pSkill5Text;

private:
	///数值显示
	cocos2d::Label *m_pKillText;
	cocos2d::Label *m_pDeathText;
	cocos2d::Label *m_pMoneyText;
	cocos2d::Label *m_pMoney2Text;
	cocos2d::Label *m_pLevelText;
	cocos2d::Label *m_pSpeedText;
	cocos2d::Label *m_pScoreText;

	//属性面板背景及按钮
	bool AttriIsOpen;
	cocos2d::Sprite *m_AttriBack1;
	cocos2d::Sprite *m_AttriBack2;
	cocos2d::MenuItemImage *m_pOpAttriMii;
	cocos2d::MenuItemImage  *m_pHeroAttriMii;
	cocos2d::MenuItemImage *m_pCloseAttri;
	cocos2d::Menu *m_pAttriMenu;

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

	cocos2d::Sprite *m_pRecomBac;
	cocos2d::Sprite *m_pAttackBac;
	cocos2d::Sprite *m_pMagicBac;
	cocos2d::Sprite *m_pDefenseBac;
	cocos2d::Sprite *m_pMoveBac;
	cocos2d::Sprite *m_pBattleBac;
	cocos2d::Sprite *m_pAssistBac;

	cocos2d::Menu *m_pRecommandMenu;
	cocos2d::MenuItemImage *m_pRecom1;
	cocos2d::MenuItemImage *m_pRecom2;
	cocos2d::MenuItemImage *m_pRecom3;
	cocos2d::MenuItemImage *m_pRecom4;
	cocos2d::MenuItemImage *m_pRecom5;

	cocos2d::Menu *m_pAttackMenu;
	cocos2d::MenuItemImage *m_pAttack1;
	cocos2d::MenuItemImage *m_pAttack2;
	cocos2d::MenuItemImage *m_pAttack3;
	cocos2d::MenuItemImage *m_pAttack4;
	cocos2d::MenuItemImage *m_pAttack5;
	cocos2d::MenuItemImage *m_pAttack6;
	cocos2d::MenuItemImage *m_pAttack7;
	cocos2d::MenuItemImage *m_pAttack8;
	cocos2d::MenuItemImage *m_pAttack9;
	cocos2d::MenuItemImage *m_pAttack10;
	cocos2d::MenuItemImage *m_pAttack11;
	cocos2d::MenuItemImage *m_pAttack12;
	cocos2d::MenuItemImage *m_pAttack13;
	cocos2d::MenuItemImage *m_pAttack14;
	cocos2d::MenuItemImage *m_pAttack15;
	cocos2d::MenuItemImage *m_pAttack16;
	cocos2d::MenuItemImage *m_pAttack17;
	cocos2d::MenuItemImage *m_pAttack18;
	cocos2d::MenuItemImage *m_pAttack19;
	cocos2d::MenuItemImage *m_pAttack20;
	cocos2d::MenuItemImage *m_pAttack21;
	cocos2d::MenuItemImage *m_pAttack22;
	cocos2d::MenuItemImage *m_pAttack23;
	cocos2d::MenuItemImage *m_pAttack24;
	cocos2d::MenuItemImage *m_pAttack25;
	cocos2d::MenuItemImage *m_pAttack26;
	cocos2d::MenuItemImage *m_pAttack27;
	cocos2d::MenuItemImage *m_pAttack28;

	cocos2d::Menu *m_pMagicMenu;
	cocos2d::MenuItemImage *m_pMagic1;
	cocos2d::MenuItemImage *m_pMagic2;
	cocos2d::MenuItemImage *m_pMagic3;
	cocos2d::MenuItemImage *m_pMagic4;
	cocos2d::MenuItemImage *m_pMagic5;
	cocos2d::MenuItemImage *m_pMagic6;
	cocos2d::MenuItemImage *m_pMagic7;
	cocos2d::MenuItemImage *m_pMagic8;
	cocos2d::MenuItemImage *m_pMagic9;
	cocos2d::MenuItemImage *m_pMagic10;
	cocos2d::MenuItemImage *m_pMagic11;
	cocos2d::MenuItemImage *m_pMagic12;
	cocos2d::MenuItemImage *m_pMagic13;
	cocos2d::MenuItemImage *m_pMagic14;
	cocos2d::MenuItemImage *m_pMagic15;
	cocos2d::MenuItemImage *m_pMagic16;
	cocos2d::MenuItemImage *m_pMagic17;
	cocos2d::MenuItemImage *m_pMagic18;
	cocos2d::MenuItemImage *m_pMagic19;
	cocos2d::MenuItemImage *m_pMagic20;
	cocos2d::MenuItemImage *m_pMagic21;
	cocos2d::MenuItemImage *m_pMagic22;
	cocos2d::MenuItemImage *m_pMagic23;
	cocos2d::MenuItemImage *m_pMagic24;

	cocos2d::Menu *m_pDefenseMenu;
	cocos2d::MenuItemImage *m_pDefense1;
	cocos2d::MenuItemImage *m_pDefense2;
	cocos2d::MenuItemImage *m_pDefense3;
	cocos2d::MenuItemImage *m_pDefense4;
	cocos2d::MenuItemImage *m_pDefense5;
	cocos2d::MenuItemImage *m_pDefense6;
	cocos2d::MenuItemImage *m_pDefense7;
	cocos2d::MenuItemImage *m_pDefense8;
	cocos2d::MenuItemImage *m_pDefense9;
	cocos2d::MenuItemImage *m_pDefense10;
	cocos2d::MenuItemImage *m_pDefense11;
	cocos2d::MenuItemImage *m_pDefense12;
	cocos2d::MenuItemImage *m_pDefense13;
	cocos2d::MenuItemImage *m_pDefense14;
	cocos2d::MenuItemImage *m_pDefense15;
	cocos2d::MenuItemImage *m_pDefense16;
	cocos2d::MenuItemImage *m_pDefense17;
	cocos2d::MenuItemImage *m_pDefense18;
	cocos2d::MenuItemImage *m_pDefense19;
	cocos2d::MenuItemImage *m_pDefense20;

	cocos2d::Menu *m_pMoveMenu;
	cocos2d::MenuItemImage *m_pMove1;
	cocos2d::MenuItemImage *m_pMove2;
	cocos2d::MenuItemImage *m_pMove3;
	cocos2d::MenuItemImage *m_pMove4;
	cocos2d::MenuItemImage *m_pMove5;
	cocos2d::MenuItemImage *m_pMove6;
	cocos2d::MenuItemImage *m_pMove7;

	cocos2d::Menu *m_pBattleMenu;
	cocos2d::MenuItemImage *m_pBattle1;
	cocos2d::MenuItemImage *m_pBattle2;
	cocos2d::MenuItemImage *m_pBattle3;
	cocos2d::MenuItemImage *m_pBattle4;
	cocos2d::MenuItemImage *m_pBattle5;
	cocos2d::MenuItemImage *m_pBattle6;
	cocos2d::MenuItemImage *m_pBattle7;

	cocos2d::Menu *m_pAssistMenu;
	cocos2d::MenuItemImage *m_pAssist1;
	cocos2d::MenuItemImage *m_pAssist2;
	cocos2d::MenuItemImage *m_pAssist3;
	cocos2d::MenuItemImage *m_pAssist4;
	cocos2d::MenuItemImage *m_pAssist5;
	cocos2d::MenuItemImage *m_pAssist6;
	cocos2d::MenuItemImage *m_pAssist7;
	cocos2d::MenuItemImage *m_pAssist8;
	cocos2d::MenuItemImage *m_pAssist9;

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
	cocos2d::MenuItemImage *pRecoverMii;
	cocos2d::MenuItemImage *pCureMii;

	cocos2d::MenuItemImage *pSkill1Mii;
	cocos2d::MenuItemImage *pSkill2Mii;
	cocos2d::MenuItemImage *pSkill3Mii;

	cocos2d::Menu *m_pSkillMenu;


public:
	//属性面板函数
	void openAttri(cocos2d::Ref* pSender);
	void transToOp(cocos2d::Ref* pSender);
	void transToHero(cocos2d::Ref* pSender);
	void closeAttri(cocos2d::Ref* pSender);
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
	void attack16(cocos2d::Ref* pSender);

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
	void magic16(cocos2d::Ref* pSender);

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
	void defense16(cocos2d::Ref* pSender);

	void move1(cocos2d::Ref* pSender);
	void move2(cocos2d::Ref* pSender);
	void move3(cocos2d::Ref* pSender);
	void move4(cocos2d::Ref* pSender);
	void move5(cocos2d::Ref* pSender);
	void move6(cocos2d::Ref* pSender);
	void move7(cocos2d::Ref* pSender);

	void battle1(cocos2d::Ref* pSender);
	void battle2(cocos2d::Ref* pSender);
	void battle3(cocos2d::Ref* pSender);
	void battle4(cocos2d::Ref* pSender);
	void battle5(cocos2d::Ref* pSender);
	void battle6(cocos2d::Ref* pSender);
	void battle7(cocos2d::Ref* pSender);

	void assist1(cocos2d::Ref* pSender);
	void assist2(cocos2d::Ref* pSender);
	void assist3(cocos2d::Ref* pSender);
	void assist4(cocos2d::Ref* pSender);
	void assist5(cocos2d::Ref* pSender);
	void assist6(cocos2d::Ref* pSender);
	void assist7(cocos2d::Ref* pSender);
	void assist8(cocos2d::Ref* pSender);
	void assist9(cocos2d::Ref* pSender);

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
	