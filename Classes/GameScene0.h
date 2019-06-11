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
	////����
	int m_kill;   //��ɱ������
	int m_death;   //������
	int e_kill;    //���ֻ�ɱ��
	int e_death;   //����������
	//int m_assist;  //������
	//int m_monster;  //��ɱҰ����
	int m_tower;///������
	int m_money;//Ŀǰ��Ǯ
	int t_money;//��ý�Ǯ
	int m_level; //�ȼ�
	int e_level;//���ֵȼ�

	float m_attack;//������
	float m_power;//����ǿ��
	int m_health;//������ֵ
	int magicpoint;//����ֵ
	float armor;//����ֵ
	float magicDenfence;//ħ��
	float attackingSpeed;  //�����ٶ�
	float waitLessen;//��ȴ����
	float velocity;//�ƶ��ٶ�
	int healthRecover;//�����ظ�
	int magicpointRecover;//�����ظ� 
	float armorIgnore;//���״�͸
	float magicdenfenceIgnore;//������͸
	float physicBloodSuck;//������Ѫ
	float magicBloodSuck;//������Ѫ

	//////װ��
	//EquipmentData s_Equip[8][30];
	cocos2d::MenuItemImage*Equipment[8][30];

private:
	///ʱ��
	char m_Textbuffer[999];
	int time_min;
	int time_sec;
	float time;
	int number;

	cocos2d::Label *m_pTime_minText;
	cocos2d::Label *m_pTime_secText;

	////������ȴ
	int m_SkillWait[6];
	int SkillWait[6];

	bool m_SkillUp[6];

	float m_pass[6];

	cocos2d::Label *m_pSkillText[6];

private:
	///////////////��ֵ��ʾ1
	cocos2d::Label *m_pKillText[4];//����
	cocos2d::Label *e_pKillText;

	cocos2d::Label *m_pDeathText;
	cocos2d::Label *m_pDeath2Text;///������ǩ

	cocos2d::Label *m_pLevelText;//�ȼ�

	cocos2d::Label *m_pMoneyText;
	cocos2d::Label *m_pMoney2Text;

	cocos2d::Label *t_pMoneyText;
	cocos2d::Label *t_pMoney2Text;

	cocos2d::Label *m_pAttri1Text[6];

	////////////////��ֵ��ʾ2��������壩
	cocos2d::Label  *m_pAttri2Text[17];
	//cocos2d::Label *m_pAttackText;     //������
	//cocos2d::Label *m_pPowerText;      //��������
	//cocos2d::Label *m_pHelthText;      //�������
	//cocos2d::Label *m_pMagicPointText;    //�����
	//cocos2d::Label *m_pArmorText;         //�������
	//cocos2d::Label *m_pMagicDefenseText;      //��������
	//cocos2d::Label *m_pAttackingSpeendText;    //�����ٶ�
	//cocos2d::Label *m_pWaitLessenText;          //��ȴ����
	//cocos2d::Label *m_pDamageChanceText;        //��������
	//cocos2d::Label *m_pVelocityText;            //�ƶ��ٶ�
	//cocos2d::Label *m_pHealthRecoverText;       //ÿ5���Ѫ
	//cocos2d::Label *m_pMagicPointRecoverText;     //ÿ5�����
	//cocos2d::Label *m_pArmorIgnoreText;          //����͸
	//cocos2d::Label *m_pMagicDefenceText;         //������͸
	//cocos2d::Label *m_pPhysicBloodSuckText;      //������Ѫ
	//cocos2d::Label *m_pMagicBloodSuckText;       //������Ѫ


	//�������1��������ť(��ս��
	bool AttriIsOpen;
	cocos2d::Sprite *m_AttriBack1;
	cocos2d::Sprite *m_AttriBack2;
	cocos2d::MenuItemImage *m_pOpAttriMii;
	cocos2d::MenuItemImage  *m_pHeroAttriMii;
	cocos2d::MenuItemImage *m_pCloseAttri;
	cocos2d::Menu *m_pAttriMenu;

	///////////////�������2��������ť��������ϸ��
	cocos2d::Sprite *m_AttriB1;
	cocos2d::Sprite *m_AttriB2;
	cocos2d::MenuItemImage *m_button1;
	cocos2d::MenuItemImage *m_button2;
	cocos2d::MenuItemImage *m_closebutton;
	cocos2d::Menu *m_AttriMenu;

	////////////�̵���弰��ť
	bool ShopIsOpen;
	cocos2d::Sprite *m_ShopBack;
	cocos2d::MenuItemImage *m_pRecomMii;
	cocos2d::MenuItemImage *m_pAttackMii;
	cocos2d::MenuItemImage *m_pMagicMii;
	cocos2d::MenuItemImage *m_pDefenseMii;
	cocos2d::MenuItemImage *m_pMoveMii;
	cocos2d::MenuItemImage *m_pBattleMii;
	cocos2d::MenuItemImage *m_pAssistMii;
	cocos2d::MenuItemImage *m_pDownMii;///��¼����ȥ��
	cocos2d::MenuItemImage *m_pCloseShop;
	cocos2d::Menu *m_pShopMenu;

	//�̵�˵�
	cocos2d::Menu *m_pDownMenu;//��¼����ȥ�ģ�
	cocos2d::Sprite *m_pDownBac;

	cocos2d::Sprite *m_pBac[8];

	cocos2d::Menu *m_pRecommandMenu;
	cocos2d::Menu *m_pAttackMenu;
	cocos2d::Menu *m_pMagicMenu;
	cocos2d::Menu *m_pDefenseMenu;
	cocos2d::Menu *m_pMoveMenu;
	cocos2d::Menu *m_pBattleMenu;
	cocos2d::Menu *m_pAssistMenu;

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
	cocos2d::MenuItemImage*pSkillMii[6];

	cocos2d::Menu *m_pSkillMenu;


public:
	//������庯��
	void transToOp(cocos2d::Ref* pSender);
	void transToHero(cocos2d::Ref* pSender);
	void closeAttri(cocos2d::Ref* pSender);

	//�������2����
	void openAttri2(cocos2d::Ref* pSender);
	void transTo1(cocos2d::Ref* pSender);
	void transTo2(cocos2d::Ref* pSender);
	void closeAttri2(cocos2d::Ref* pSender);

	///////////////////�̵���庯��
	void openShop(cocos2d::Ref* pSender);
	void closeShop(cocos2d::Ref* pSender);

	void RecommendMenu(cocos2d::Ref* pSender);
	void AttackMenu(cocos2d::Ref* pSender);
	void MagicMenu(cocos2d::Ref* pSender);
	void DefenseMenu(cocos2d::Ref* pSender);
	void MoveMenu(cocos2d::Ref* pSender);
	void BattleMenu(cocos2d::Ref* pSender);
	void AssistMenu(cocos2d::Ref* pSender);

	//��Ʒ��������
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

	virtual void GameScene0::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual bool init();

	virtual void update(float delta);


	CREATE_FUNC(GameScene0);
};

#endif 
