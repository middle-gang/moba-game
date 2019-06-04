
#ifndef __HUDLayer_H__
#define __HUDLayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class HUDLayer : public cocos2d::Layer
{
private:
	///ʱ��
	char m_textContain[100];
	int time_min;
	int time_sec;
	float time;
	int number;

	cocos2d::Label *m_pTime_minText;
	cocos2d::Label *m_pTime_secText;

	////������ȴ
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

	////����
	int m_kill;   //��ɱ������
	int m_death;   //������
	//int m_assist;  //������
	//int m_monster;  
	int m_tower;
	int m_money;
	int m_Score;
	int m_Level;

private:
	///��ֵ��ʾ
	char m_Textbuffer[999];
	cocos2d::Label *m_pKillText;
	cocos2d::Label *m_pDeathText;

	cocos2d::Label *m_pLevelText;
	cocos2d::Label *m_pSpeedText;
	cocos2d::Label *m_pScoreText;

	//������屳������ť
	bool AttriIsOpen;
	cocos2d::Sprite *m_AttriBack1;
	cocos2d::Sprite *m_AttriBack2;
	cocos2d::MenuItemImage *m_pOpAttriMii;
	cocos2d::MenuItemImage  *m_pHeroAttriMii;
	cocos2d::MenuItemImage *m_pCloseAttri;
	cocos2d::Menu *m_pAttriMenu;

	//�̵���弰��ť
	bool ShopIsOpen;
	cocos2d::Sprite *m_ShopBack;
	cocos2d::MenuItemImage *m_pRecomMii;
	cocos2d::MenuItemImage *m_pAttackMii;
	cocos2d::MenuItemImage *m_pMagicMii;
	cocos2d::MenuItemImage *m_pDefenseMii;
	cocos2d::MenuItemImage *m_pMoveMii;
	cocos2d::MenuItemImage *m_pBattleMii;
	cocos2d::MenuItemImage *m_pAssistMii;
	cocos2d::MenuItemImage *m_pDownMii;
	cocos2d::MenuItemImage *m_pCloseShop;
	cocos2d::Menu *m_pShopMenu;

	//ѯ���˳����漰��ť
	bool ExitIsOpen;
	cocos2d::Sprite *m_ExitBack;
	cocos2d::MenuItemImage *m_pYesMii;
	cocos2d::MenuItemImage *m_pNoMii;
	cocos2d::Menu *m_pExitMenu;

	bool m_IsPopDialog;
	float m_DialogPopTime;

	//�����ɰ�
	cocos2d::Sprite *m_pMaskImage;

	//��ʾ��ť�����ԣ��̵꣬�˳�
	cocos2d::Menu *m_pMenu;

	//�������
	cocos2d::MenuItemImage *pAttackMii;
	cocos2d::MenuItemImage *pRecoverMii;
	cocos2d::MenuItemImage *pCureMii;

	cocos2d::MenuItemImage *pSkill1Mii;
	cocos2d::MenuItemImage *pSkill2Mii;
	cocos2d::MenuItemImage *pSkill3Mii;

	cocos2d::Menu *m_pSkillMenu;


public:
	//������庯��
	void openAttri(cocos2d::Ref* pSender);
	void transToOp(cocos2d::Ref* pSender);
	void transToHero(cocos2d::Ref* pSender);
	void closeAttri(cocos2d::Ref* pSender);
	//�̵���庯��
	void openShop(cocos2d::Ref* pSender);
	void closeShop(cocos2d::Ref* pSender);
	void RecommendMenu(cocos2d::Ref* pSender);
	void AttackMenu(cocos2d::Ref* pSender);
	void MagicMenu(cocos2d::Ref* pSender);
	void DefenseMenu(cocos2d::Ref* pSender);
	void MoveMenu(cocos2d::Ref* pSender);
	void BattleMenu(cocos2d::Ref* pSender);
	void AssistMenu(cocos2d::Ref* pSender);
	//�˳����溯��
	void openExit(cocos2d::Ref* pSender);
	void menuYesCallback(cocos2d::Ref* pSender);
	void menuNoCallback(cocos2d::Ref* pSender);
	///���ܺ���
	void Skill1(cocos2d::Ref* pSender);
	void Skill2(cocos2d::Ref* pSender);
	void Skill3(cocos2d::Ref* pSender);

	void attack(cocos2d::Ref* pSender);
	void recover(cocos2d::Ref* pSender);
	void cure(cocos2d::Ref* pSender);


	public:
	static cocos2d::Scene* createScene();

	virtual void HUDLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual bool init();

	virtual void update(float delta);


	CREATE_FUNC(HUDLayer);
};

#endif // __HELLOWORLD_SCENE_H__
