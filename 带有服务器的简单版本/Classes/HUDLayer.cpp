#include "HUDLayer.h"
#include "SimpleAudioEngine.h"
#include"GlobalVal.h"
#include"HelloWorldScene.h"

USING_NS_CC;

Scene* HUDLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HUDLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HUDLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////游戏时间
	////游戏时间
	time_min = 0;
	time_sec = 0;
	time = 0;
	number = 0;

	sprintf(m_textContain, "%d", time_min);
	m_pTime_minText = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 23);
	m_pTime_minText->setPosition(80, 405);
	addChild(m_pTime_minText, 3);

	sprintf(m_textContain, "%d", time_sec);
	m_pTime_secText = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 23);
	m_pTime_secText->setPosition(110, 405);
	addChild(m_pTime_secText, 3);

	///技能冷却时间
	m_Skill1Wait = 8;
	m_Skill2Wait = 12;
	m_Skill3Wait = 18;
	m_Skill4Wait = 10;
	m_Skill5Wait = 15;
	
	m_pass1 = 0;
	m_pass2 = 0;
	m_pass3 = 0;
	m_pass4 = 0;
	m_pass5 = 0;

	m_Skill1Up = true;
	m_Skill2Up = true;
	m_Skill3Up = true;
	m_Skill4Up = true;
	m_Skill5Up = true;

	sprintf(m_textContain, "%d", m_Skill1Wait);
	m_pSkill1Text = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 20);
	m_pSkill1Text->setPosition(80, 145);
	addChild(m_pSkill1Text, 3);
	m_pSkill1Text->setVisible(false);

	sprintf(m_textContain, "%d", m_Skill2Wait);
	m_pSkill2Text = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 20);
	m_pSkill2Text->setPosition(130, 85);
	addChild(m_pSkill2Text, 3);
	m_pSkill2Text->setVisible(false);

	sprintf(m_textContain, "%d", m_Skill3Wait);
	m_pSkill3Text = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 20);
	m_pSkill3Text->setPosition(80, 25);
	addChild(m_pSkill3Text, 3);
	m_pSkill3Text->setVisible(false);

	sprintf(m_textContain, "%d", m_Skill4Wait);
	m_pSkill4Text = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 20);
	m_pSkill4Text->setPosition(150, 20);
	addChild(m_pSkill4Text, 3);
	m_pSkill4Text->setVisible(false);

	sprintf(m_textContain, "%d", m_Skill5Wait);
	m_pSkill5Text = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 20);
	m_pSkill5Text->setPosition(200, 20);
	addChild(m_pSkill5Text, 3);
	m_pSkill5Text->setVisible(false);

	//创建属性界面
	AttriIsOpen = false;
	MenuItemImage* pAttriWin = MenuItemImage::create("photo/main/box1.png", "photo/main/box1.png",
		CC_CALLBACK_1(HUDLayer::openAttri, this));
	pAttriWin->setPosition(160, 420);

	m_AttriBack1 = Sprite::create("photo/Attribute/dialog1.png");
	m_AttriBack1->setPosition(500, 236.5);
	addChild(m_AttriBack1, 11);
	m_AttriBack1->setVisible(false);

	m_AttriBack2 = Sprite::create("photo/Attribute/dialog2.png");
	m_AttriBack2->setPosition(500, 236.5);
	addChild(m_AttriBack2, 11);
	m_AttriBack2->setVisible(false);

	m_pOpAttriMii = MenuItemImage::create("photo/Attribute/opP_up.png",
		"photo/Attribute/opP_down.png",
		"photo/Attribute/opP_down.png",
		CC_CALLBACK_1(HUDLayer::transToOp, this));
	m_pOpAttriMii->setPosition(198, 390);
	m_pOpAttriMii->setEnabled(false);

	m_pHeroAttriMii = MenuItemImage::create("photo/Attribute/heroP_up.png",
		"photo/Attribute/heroP_down.png",
		"photo/Attribute/heroP_down.png",
		CC_CALLBACK_1(HUDLayer::transToHero, this));
	m_pHeroAttriMii->setPosition(370, 390);

	m_pCloseAttri = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(HUDLayer::closeAttri, this));
	m_pCloseAttri->setPosition(870, 400);

	m_pAttriMenu = Menu::create(m_pOpAttriMii, m_pHeroAttriMii, m_pCloseAttri, NULL);
	m_pAttriMenu->setPosition(Vec2::ZERO);
	addChild(m_pAttriMenu, 12);
	m_pAttriMenu->setVisible(false);


	//属性数值显示
	Label* m_pAssist = Label::createWithTTF("0", "fonts/msyh.ttc", 23);
	m_pAssist->setPosition(200, 435);
	addChild(m_pAssist, 3);
	 
	m_kill = obj.m_kill;
	sprintf(m_Textbuffer, "%d", m_kill);
	m_pKillText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKillText->setPosition(160, 435);
	addChild(m_pKillText, 3);

	/////////////////////////////创建商店界面
	ShopIsOpen = false;
	MenuItemImage * pShopWin = MenuItemImage::create("photo/shop.png", "photo/shop1.png",
		CC_CALLBACK_1(HUDLayer::openShop, this));
	pShopWin->setPosition(930, 200);

	//////金钱显示
	e_money = obj.e_money;
	sprintf(m_Textbuffer, "%d", e_money);
	e_pMoney = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 15);
	e_pMoney->setColor(Color3B::BLACK);
	e_pMoney->setPosition(928,189);
	addChild(e_pMoney, 3);

	sprintf(m_Textbuffer, "%d", e_money2);
	e_pMoney2 = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	e_pMoney2->setColor(Color3B::BLUE);
	e_pMoney2->setPosition(180,375);
	e_pMoney2->setVisible(false);
	addChild(e_pMoney2, 13);


	m_ShopBack = Sprite::create("photo/shop/background.png");
	m_ShopBack->setPosition(500, 236.5);
	addChild(m_ShopBack, 11);
	m_ShopBack->setVisible(false);

	///////////////商店物品
	////推荐
	m_pRecom1 = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pRecom2= MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pRecom3 = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pRecom4 = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pRecom5 = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pRecom1->setPosition(270, 370);   m_pRecom2->setPosition(390, 370);   m_pRecom3->setPosition(510, 370);   m_pRecom4->setPosition(630, 370);
	m_pRecom5->setPosition(270, 285);

	m_pRecom1->setEnabled(false);   m_pRecom2->setEnabled(false);   m_pRecom3->setEnabled(false);   m_pRecom4->setEnabled(false);
	m_pRecom5->setEnabled(false);

	m_pRecommandMenu = Menu::create(m_pRecom1, m_pRecom2, m_pRecom3, m_pRecom4,
		                            m_pRecom5,NULL);
	m_pRecommandMenu->setPosition(Vec2::ZERO);
	addChild(m_pRecommandMenu, 13);
	m_pRecommandMenu->setVisible(false);

	/////攻击
	m_pAttack1 = MenuItemImage::create("photo/shop/attack/1.jpg",
		"photo/shop/attack/1_1.jpg",
		"photo/shop/attack/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack2 = MenuItemImage::create("photo/shop/attack/2.jpg",
		"photo/shop/attack/2_1.jpg",
		"photo/shop/attack/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack3 = MenuItemImage::create("photo/shop/attack/3.jpg",
		"photo/shop/attack/3_1.jpg",
		"photo/shop/attack/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack4 = MenuItemImage::create("photo/shop/attack/4.jpg",
		"photo/shop/attack/4_1.jpg",
		"photo/shop/attack/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack5 = MenuItemImage::create("photo/shop/attack/5.jpg",
		"photo/shop/attack/5_1.jpg",
		"photo/shop/attack/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack6 = MenuItemImage::create("photo/shop/attack/6.jpg",
		"photo/shop/attack/6_1.jpg",
		"photo/shop/attack/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack7 = MenuItemImage::create("photo/shop/attack/7.jpg",
		"photo/shop/attack/7_1.jpg",
		"photo/shop/attack/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack8 = MenuItemImage::create("photo/shop/attack/8.jpg",
		"photo/shop/attack/8_1.jpg",
		"photo/shop/attack/8_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack9 = MenuItemImage::create("photo/shop/attack/9.jpg",
		"photo/shop/attack/9_1.jpg",
		"photo/shop/attack/9_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack10 = MenuItemImage::create("photo/shop/attack/10.jpg",
		"photo/shop/attack/10_1.jpg",
		"photo/shop/attack/10_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack11 = MenuItemImage::create("photo/shop/attack/11.jpg",
		"photo/shop/attack/11_1.jpg",
		"photo/shop/attack/11_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack12 = MenuItemImage::create("photo/shop/attack/12.jpg",
		"photo/shop/attack/12_1.jpg",
		"photo/shop/attack/12_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack13 = MenuItemImage::create("photo/shop/attack/13.jpg",
		"photo/shop/attack/13_1.jpg",
		"photo/shop/attack/13_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack14 = MenuItemImage::create("photo/shop/attack/14.jpg",
		"photo/shop/attack/14_1.jpg",
		"photo/shop/attack/14_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack15 = MenuItemImage::create("photo/shop/attack/15.jpg",
		"photo/shop/attack/15_1.jpg",
		"photo/shop/attack/15_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAttack16 = MenuItemImage::create("photo/shop/attack/16.jpg",
		"photo/shop/attack/16_1.jpg",
		"photo/shop/attack/16_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pAttack1->setPosition(270,370);   m_pAttack2->setPosition(390, 370);   m_pAttack3->setPosition(510, 370);   m_pAttack4->setPosition(630, 370);
	m_pAttack5->setPosition(270, 285);  m_pAttack6->setPosition(390, 285);   m_pAttack7->setPosition(510, 285);   m_pAttack8->setPosition(630, 285);
	m_pAttack9->setPosition(270, 200);  m_pAttack10->setPosition(390, 200);  m_pAttack11->setPosition(510, 200);  m_pAttack12->setPosition(630, 200);
	m_pAttack13->setPosition(270, 115); m_pAttack14->setPosition(390, 115);  m_pAttack15->setPosition(510, 115);  m_pAttack16->setPosition(630, 115);

	m_pAttack1->setEnabled(false);   m_pAttack2->setEnabled(false);   m_pAttack3->setEnabled(false);   m_pAttack4->setEnabled(false);
	m_pAttack5->setEnabled(false);   m_pAttack6->setEnabled(false);   m_pAttack7->setEnabled(false);   m_pAttack8->setEnabled(false);
	m_pAttack9->setEnabled(false);   m_pAttack10->setEnabled(false);  m_pAttack11->setEnabled(false);  m_pAttack12->setEnabled(false);
	m_pAttack13->setEnabled(false);  m_pAttack14->setEnabled(false);  m_pAttack15->setEnabled(false);  m_pAttack16->setEnabled(false);

	m_pAttackMenu = Menu::create(m_pAttack1,m_pAttack2,m_pAttack3,m_pAttack4,
		                         m_pAttack5, m_pAttack6, m_pAttack7, m_pAttack8,
		                         m_pAttack9,m_pAttack10,m_pAttack11,m_pAttack12,
		                         m_pAttack13,m_pAttack14,m_pAttack15,m_pAttack16,NULL);
	m_pAttackMenu->setPosition(Vec2::ZERO);
	addChild(m_pAttackMenu, 13);
	m_pAttackMenu->setVisible(false);

	//法术
	m_pMagic1 = MenuItemImage::create("photo/shop/magic/1.jpg",
		"photo/shop/magic/1_1.jpg",
		"photo/shop/magic/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic2 = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic3 = MenuItemImage::create("photo/shop/magic/3.jpg",
		"photo/shop/magic/3_1.jpg",
		"photo/shop/magic/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic4 = MenuItemImage::create("photo/shop/magic/4.jpg",
		"photo/shop/magic/4_1.jpg",
		"photo/shop/magic/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic5 = MenuItemImage::create("photo/shop/magic/5.jpg",
		"photo/shop/magic/5_1.jpg",
		"photo/shop/magic/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic6 = MenuItemImage::create("photo/shop/magic/6.jpg",
		"photo/shop/magic/6_1.jpg",
		"photo/shop/magic/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic7 = MenuItemImage::create("photo/shop/magic/7.jpg",
		"photo/shop/magic/7_1.jpg",
		"photo/shop/magic/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic8 = MenuItemImage::create("photo/shop/magic/8.jpg",
		"photo/shop/magic/8_1.jpg",
		"photo/shop/magic/8_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic9 = MenuItemImage::create("photo/shop/magic/9.jpg",
		"photo/shop/magic/9_1.jpg",
		"photo/shop/magic/9_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic10 = MenuItemImage::create("photo/shop/magic/10.jpg",
		"photo/shop/magic/10_1.jpg",
		"photo/shop/magic/10_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic11 = MenuItemImage::create("photo/shop/magic/11.jpg",
		"photo/shop/magic/11_1.jpg",
		"photo/shop/magic/11_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic12 = MenuItemImage::create("photo/shop/magic/12.jpg",
		"photo/shop/magic/12_1.jpg",
		"photo/shop/magic/12_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic13 = MenuItemImage::create("photo/shop/magic/13.jpg",
		"photo/shop/magic/13_1.jpg",
		"photo/shop/magic/13_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic14 = MenuItemImage::create("photo/shop/magic/14.jpg",
		"photo/shop/magic/14_1.jpg",
		"photo/shop/magic/14_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic15 = MenuItemImage::create("photo/shop/magic/15.jpg",
		"photo/shop/magic/15_1.jpg",
		"photo/shop/magic/15_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMagic16 = MenuItemImage::create("photo/shop/magic/16.jpg",
		"photo/shop/magic/16_1.jpg",
		"photo/shop/magic/16_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pMagic1->setPosition(270, 370);  m_pMagic2->setPosition(390, 370);   m_pMagic3->setPosition(510, 370);    m_pMagic4->setPosition(630, 370);
	m_pMagic5->setPosition(270, 285);  m_pMagic6->setPosition(390, 285);   m_pMagic7->setPosition(510, 285);   m_pMagic8->setPosition(630, 285);
	m_pMagic9->setPosition(270, 200);  m_pMagic10->setPosition(390, 200);  m_pMagic11->setPosition(510, 200);  m_pMagic12->setPosition(630, 200);
	m_pMagic13->setPosition(270, 115); m_pMagic14->setPosition(390, 115);  m_pMagic15->setPosition(510, 115);  m_pMagic16->setPosition(630, 115);

	m_pMagic1->setEnabled(false);   m_pMagic2->setEnabled(false);   m_pMagic3->setEnabled(false);   m_pMagic4->setEnabled(false);
	m_pMagic5->setEnabled(false);   m_pMagic6->setEnabled(false);   m_pMagic7->setEnabled(false);   m_pMagic8->setEnabled(false);
	m_pMagic9->setEnabled(false);   m_pMagic10->setEnabled(false);  m_pMagic11->setEnabled(false);  m_pMagic12->setEnabled(false);
	m_pMagic13->setEnabled(false);  m_pMagic14->setEnabled(false);  m_pMagic15->setEnabled(false);  m_pMagic16->setEnabled(false);

	m_pMagicMenu = Menu::create(m_pMagic1,m_pMagic2,m_pMagic3,m_pMagic4,
		                        m_pMagic5,m_pMagic6,m_pMagic7,m_pMagic8,
		                        m_pMagic9,m_pMagic10,m_pMagic11,m_pMagic12,
		                        m_pMagic13,m_pMagic14,m_pMagic15,m_pMagic16,NULL);
	m_pMagicMenu->setPosition(Vec2::ZERO);
	addChild(m_pMagicMenu, 13);
	m_pMagicMenu->setVisible(false);

	///防御
	m_pDefense1 = MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense2 = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense3 = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense4 = MenuItemImage::create("photo/shop/defense/4.jpg",
		"photo/shop/defense/4_1.jpg",
		"photo/shop/defense/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense5 = MenuItemImage::create("photo/shop/defense/5.jpg",
		"photo/shop/defense/5_1.jpg",
		"photo/shop/defense/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense6 = MenuItemImage::create("photo/shop/defense/6.jpg",
		"photo/shop/defense/6_1.jpg",
		"photo/shop/defense/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense7 = MenuItemImage::create("photo/shop/defense/7.jpg",
		"photo/shop/defense/7_1.jpg",
		"photo/shop/defense/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense8 = MenuItemImage::create("photo/shop/defense/8.jpg",
		"photo/shop/defense/8_1.jpg",
		"photo/shop/defense/8_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense9 = MenuItemImage::create("photo/shop/defense/9.jpg",
		"photo/shop/defense/9_1.jpg",
		"photo/shop/defense/9_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense10 = MenuItemImage::create("photo/shop/defense/10.jpg",
		"photo/shop/defense/10_1.jpg",
		"photo/shop/defense/10_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense11 = MenuItemImage::create("photo/shop/defense/11.jpg",
		"photo/shop/defense/11_1.jpg",
		"photo/shop/defense/11_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense12 = MenuItemImage::create("photo/shop/defense/12.jpg",
		"photo/shop/defense/12_1.jpg",
		"photo/shop/defense/12_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense13 = MenuItemImage::create("photo/shop/defense/13.jpg",
		"photo/shop/defense/13_1.jpg",
		"photo/shop/defense/13_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense14 = MenuItemImage::create("photo/shop/defense/14.jpg",
		"photo/shop/defense/14_1.jpg",
		"photo/shop/defense/14_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense15 = MenuItemImage::create("photo/shop/defense/15.jpg",
		"photo/shop/defense/15_1.jpg",
		"photo/shop/defense/15_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pDefense16 = MenuItemImage::create("photo/shop/defense/16.jpg",
		"photo/shop/defense/16_1.jpg",
		"photo/shop/defense/16_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pDefense1->setPosition(270, 370);  m_pDefense2->setPosition(390, 370);   m_pDefense3->setPosition(510, 370);    m_pDefense4->setPosition(630, 370);
	m_pDefense5->setPosition(270, 285);  m_pDefense6->setPosition(390, 285);   m_pDefense7->setPosition(510, 285);   m_pDefense8->setPosition(630, 285);
	m_pDefense9->setPosition(270, 200);  m_pDefense10->setPosition(390, 200);  m_pDefense11->setPosition(510, 200);  m_pDefense12->setPosition(630, 200);
	m_pDefense13->setPosition(270, 115); m_pDefense14->setPosition(390, 115);  m_pDefense15->setPosition(510, 115);  m_pDefense16->setPosition(630, 115);

	m_pDefense1->setEnabled(false);   m_pDefense2->setEnabled(false);   m_pDefense3->setEnabled(false);   m_pDefense4->setEnabled(false);
	m_pDefense5->setEnabled(false);   m_pDefense6->setEnabled(false);   m_pDefense7->setEnabled(false);   m_pDefense8->setEnabled(false);
	m_pDefense9->setEnabled(false);   m_pDefense10->setEnabled(false);  m_pDefense11->setEnabled(false);  m_pDefense12->setEnabled(false);
	m_pDefense13->setEnabled(false);  m_pDefense14->setEnabled(false);  m_pDefense15->setEnabled(false);  m_pDefense16->setEnabled(false);

	m_pDefenseMenu = Menu::create(m_pDefense1, m_pDefense2, m_pDefense3, m_pDefense4,
		                          m_pDefense5, m_pDefense6, m_pDefense7, m_pDefense8,
		                          m_pDefense9, m_pDefense10, m_pDefense11, m_pDefense12,
		                          m_pDefense13, m_pDefense14, m_pDefense15, m_pDefense16, NULL);
	m_pDefenseMenu->setPosition(Vec2::ZERO);
	addChild(m_pDefenseMenu, 13);
	m_pDefenseMenu->setVisible(false);

	///移动
	m_pMove1 = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove2 = MenuItemImage::create("photo/shop/move/2.jpg",
		"photo/shop/move/2_1.jpg",
		"photo/shop/move/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove3 = MenuItemImage::create("photo/shop/move/3.jpg",
		"photo/shop/move/3_1.jpg",
		"photo/shop/move/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove4 = MenuItemImage::create("photo/shop/move/4.jpg",
		"photo/shop/move/4_1.jpg",
		"photo/shop/move/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove5 = MenuItemImage::create("photo/shop/move/5.jpg",
		"photo/shop/move/5_1.jpg",
		"photo/shop/move/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove6 = MenuItemImage::create("photo/shop/move/6.jpg",
		"photo/shop/move/6_1.jpg",
		"photo/shop/move/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pMove7 = MenuItemImage::create("photo/shop/move/7.jpg",
		"photo/shop/move/7_1.jpg",
		"photo/shop/move/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pMove1->setPosition(270, 370);   m_pMove2->setPosition(390, 370);    m_pMove3->setPosition(510, 370);    m_pMove4->setPosition(630, 370);
	m_pMove5->setPosition(270, 285);  m_pMove6->setPosition(390, 285);   m_pMove7->setPosition(510, 285);   
	
	m_pMove1->setEnabled(false);   m_pMove2->setEnabled(false);   m_pMove3->setEnabled(false);   m_pMove4->setEnabled(false);
	m_pMove5->setEnabled(false);   m_pMove6->setEnabled(false);   m_pMove7->setEnabled(false);  

	m_pMoveMenu = Menu::create(m_pMove1, m_pMove2, m_pMove3, m_pMove4,
		m_pMove5, m_pMove6, m_pMove7,  NULL);
	m_pMoveMenu->setPosition(Vec2::ZERO);
	addChild(m_pMoveMenu, 13);
	m_pMoveMenu->setVisible(false);

	///打野
	m_pBattle1 = MenuItemImage::create("photo/shop/battle/1.jpg",
		"photo/shop/battle/1_1.jpg",
		"photo/shop/battle/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle2 = MenuItemImage::create("photo/shop/battle/2.jpg",
		"photo/shop/battle/2_1.jpg",
		"photo/shop/battle/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle3 = MenuItemImage::create("photo/shop/battle/3.jpg",
		"photo/shop/battle/3_1.jpg",
		"photo/shop/battle/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle4 = MenuItemImage::create("photo/shop/battle/4.jpg",
		"photo/shop/battle/4_1.jpg",
		"photo/shop/battle/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle5 = MenuItemImage::create("photo/shop/battle/5.jpg",
		"photo/shop/battle/5_1.jpg",
		"photo/shop/battle/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle6 = MenuItemImage::create("photo/shop/battle/6.jpg",
		"photo/shop/battle/6_1.jpg",
		"photo/shop/battle/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pBattle7 = MenuItemImage::create("photo/shop/battle/7.jpg",
		"photo/shop/battle/7_1.jpg",
		"photo/shop/battle/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pBattle1->setPosition(270, 370);   m_pBattle2->setPosition(390, 370);    m_pBattle3->setPosition(510, 370);    m_pBattle4->setPosition(630, 370);
	m_pBattle5->setPosition(270, 285);  m_pBattle6->setPosition(390, 285);   m_pBattle7->setPosition(510, 285);

	m_pBattle1->setEnabled(false);   m_pBattle2->setEnabled(false);   m_pBattle3->setEnabled(false);   m_pBattle4->setEnabled(false);
	m_pBattle5->setEnabled(false);   m_pBattle6->setEnabled(false);   m_pBattle7->setEnabled(false);

	m_pBattleMenu = Menu::create(m_pBattle1, m_pBattle2, m_pBattle3, m_pBattle4,
		m_pBattle5, m_pBattle6, m_pBattle7, NULL);
	m_pBattleMenu->setPosition(Vec2::ZERO);
	addChild(m_pBattleMenu, 13);
	m_pBattleMenu->setVisible(false);

	///辅助
	m_pAssist1 = MenuItemImage::create("photo/shop/assist/1.jpg",
		"photo/shop/assist/1_1.jpg",
		"photo/shop/assist/1_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist2 = MenuItemImage::create("photo/shop/assist/2.jpg",
		"photo/shop/assist/2_1.jpg",
		"photo/shop/assist/2_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist3 = MenuItemImage::create("photo/shop/assist/3.jpg",
		"photo/shop/assist/3_1.jpg",
		"photo/shop/assist/3_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist4 = MenuItemImage::create("photo/shop/assist/4.jpg",
		"photo/shop/assist/4_1.jpg",
		"photo/shop/assist/4_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist5 = MenuItemImage::create("photo/shop/assist/5.jpg",
		"photo/shop/assist/5_1.jpg",
		"photo/shop/assist/5_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist6 = MenuItemImage::create("photo/shop/assist/6.jpg",
		"photo/shop/assist/6_1.jpg",
		"photo/shop/assist/6_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist7 = MenuItemImage::create("photo/shop/assist/7.jpg",
		"photo/shop/assist/7_1.jpg",
		"photo/shop/assist/7_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist8 = MenuItemImage::create("photo/shop/assist/8.jpg",
		"photo/shop/assist/8_1.jpg",
		"photo/shop/assist/8_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pAssist9 = MenuItemImage::create("photo/shop/assist/9.jpg",
		"photo/shop/assist/9_1.jpg",
		"photo/shop/assist/9_1.jpg",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));

	m_pAssist1->setPosition(270, 370);  m_pAssist2->setPosition(390, 370);   m_pAssist3->setPosition(510, 370);    m_pAssist4->setPosition(630, 370);
	m_pAssist5->setPosition(270, 285);  m_pAssist6->setPosition(390, 285);   m_pAssist7->setPosition(510, 285);   m_pAssist8->setPosition(630, 285);
	m_pAssist9->setPosition(270, 200);  

	m_pAssist1->setEnabled(false);   m_pAssist2->setEnabled(false);   m_pAssist3->setEnabled(false);   m_pAssist4->setEnabled(false);
	m_pAssist5->setEnabled(false);   m_pAssist6->setEnabled(false);   m_pAssist7->setEnabled(false);   m_pAssist8->setEnabled(false);
	m_pAssist9->setEnabled(false);   

	m_pAssistMenu = Menu::create(m_pAssist1, m_pAssist2, m_pAssist3, m_pAssist4,
		m_pAssist5, m_pAssist6, m_pAssist7, m_pAssist8,
		m_pAssist9, NULL);
	m_pAssistMenu->setPosition(Vec2::ZERO);
	addChild(m_pAssistMenu, 13);
	m_pAssistMenu->setVisible(false);

	////切换按键
	m_pRecomMii = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(HUDLayer::RecommendMenu, this));
	m_pRecomMii->setPosition(166, 328);

	m_pAttackMii = MenuItemImage::create("photo/shop/attack.png",
		"photo/shop/attack1.png",
		"photo/shop/attack1.png",
		CC_CALLBACK_1(HUDLayer::AttackMenu, this));
	m_pAttackMii->setPosition(166, 286);

	m_pMagicMii = MenuItemImage::create("photo/shop/Magic.png",
		"photo/shop/Magic1.png",
		"photo/shop/Magic1.png",
		CC_CALLBACK_1(HUDLayer::MagicMenu, this));
	m_pMagicMii->setPosition(166, 244);

	m_pDefenseMii = MenuItemImage::create("photo/shop/defense.png",
		"photo/shop/defense1.png",
		"photo/shop/defense1.png",
		CC_CALLBACK_1(HUDLayer::DefenseMenu, this));
	m_pDefenseMii->setPosition(166, 202);

	m_pMoveMii = MenuItemImage::create("photo/shop/move.png",
		"photo/shop/move1.png",
		"photo/shop/move1.png",
		CC_CALLBACK_1(HUDLayer::MoveMenu, this));
	m_pMoveMii->setPosition(166, 160);

	m_pBattleMii = MenuItemImage::create("photo/shop/battle.png",
		"photo/shop/battle1.png",
		"photo/shop/battle1.png",
		CC_CALLBACK_1(HUDLayer::BattleMenu, this));
	m_pBattleMii->setPosition(166, 118);

	m_pAssistMii = MenuItemImage::create("photo/shop/assist.png",
		"photo/shop/assist1.png",
		"photo/shop/assist1.png",
		CC_CALLBACK_1(HUDLayer::AssistMenu, this));
	m_pAssistMii->setPosition(166, 76);

	//记录按下去的
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
	//////关闭按钮
	m_pCloseShop = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(HUDLayer::closeShop, this));
	m_pCloseShop->setPosition(870, 400);

	m_pShopMenu = Menu::create(m_pRecomMii, m_pAttackMii, m_pMagicMii, m_pDefenseMii, m_pMoveMii, m_pBattleMii, m_pAssistMii, m_pCloseShop, NULL);
	m_pShopMenu->setPosition(Vec2::ZERO);
	addChild(m_pShopMenu, 12);
	m_pShopMenu->setVisible(false);


	//退出询问界面
	ExitIsOpen = false;
	MenuItemImage* pExitWin = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HUDLayer::openExit, this));
	pExitWin->setPosition(Vec2(origin.x + visibleSize.width - pExitWin->getContentSize().width / 2.0f, origin.y + visibleSize.height - pExitWin->getContentSize().height / 2.0f));

	m_ExitBack = Sprite::create("image/gamescene/exit_dialog.png");
	m_ExitBack->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
	addChild(m_ExitBack, 11);
	m_ExitBack->setVisible(false);

	m_pYesMii = MenuItemImage::create("image/gamescene/yes_btn_up.png", "image/gamescene/yes_btn_down.png",
		CC_CALLBACK_1(HUDLayer::menuYesCallback, this));
	m_pYesMii->setPosition(origin.x + visibleSize.width / 2.0f - 100.0f, origin.y + visibleSize.height / 2.0f - 50);

	m_pNoMii = MenuItemImage::create("image/gamescene/no_btn_up.png", "image/gamescene/no_btn_down.png",
		CC_CALLBACK_1(HUDLayer::menuNoCallback, this));
	m_pNoMii->setPosition(origin.x + visibleSize.width / 2.0f + 100.0f, origin.y + visibleSize.height / 2.0f - 50);

	m_pExitMenu = Menu::create(m_pYesMii, m_pNoMii, NULL);
	m_pExitMenu->setPosition(Vec2::ZERO);
	addChild(m_pExitMenu, 12);
	m_pExitMenu->setVisible(false);


	//创建蒙版
	m_pMaskImage = Sprite::create("image/gamescene/maskimage.png");
	m_pMaskImage->setScale(150);
	m_pMaskImage->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
	addChild(m_pMaskImage, 10);
	m_pMaskImage->setVisible(false);

	//菜单整合，关闭按钮  技能   商店   属性
	m_pMenu = Menu::create(pAttriWin, pShopWin, pExitWin, NULL);
	m_pMenu->setPosition(Vec2::ZERO);
	addChild(m_pMenu, 0);

	//小地图
	//小地图背景
	Sprite *pSmallMap = Sprite::create("photo/smallMap.png");
	pSmallMap->setPosition(900, 390);
	addChild(pSmallMap, 1);


	//////////////技能面板
	//通用技能
	pAttackMii = MenuItemImage::create("photo/attack.png", "photo/attack-1.png",
		CC_CALLBACK_1(HUDLayer::attack, this));
	pAttackMii->setPosition(40, 90);

	pRecoverMii = MenuItemImage::create("photo/recover.png", "photo/recover1.png", "photo/recover1.png",
		CC_CALLBACK_1(HUDLayer::recover, this));
	pRecoverMii->setPosition(145, 25);

	pCureMii = MenuItemImage::create("photo/cure.png", "photo/cure1.png", "photo/cure1.png",
		CC_CALLBACK_1(HUDLayer::cure, this));
	pCureMii->setPosition(195, 25);

	//人物技能
	if (myChoice == 1)
	{
		pSkill1Mii = MenuItemImage::create("photo/Houyi/Houyi1.png", "photo/Houyi/Houyi1-2.png", "photo/Houyi/Houyi1-2.png",
			CC_CALLBACK_1(HUDLayer::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Houyi/Houyi2.png", "photo/Houyi/Houyi2-2.png", "photo/Houyi/Houyi2-2.png",
			CC_CALLBACK_1(HUDLayer::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Houyi/Houyi3.png", "photo/Houyi/Houyi3-2.png", "photo/Houyi/Houyi3-2.png",
			CC_CALLBACK_1(HUDLayer::Skill3, this));
	}
	else if (myChoice == 2)
	{
		pSkill1Mii = MenuItemImage::create("photo/Arthur/Arthur1.png", "photo/Arthur/Arthur1-2.png", "photo/Arthur/Arthur1-2.png",
			CC_CALLBACK_1(HUDLayer::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Arthur/Arthur2.png", "photo/Arthur/Arthur2-2.png", "photo/Arthur/Arthur2-2.png",
			CC_CALLBACK_1(HUDLayer::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Arthur/Arthur3.png", "photo/Arthur/Arthur3-2.png", "photo/Arthur/Arthur3-2.png",
			CC_CALLBACK_1(HUDLayer::Skill3, this));
	}
	else
	{
		pSkill1Mii = MenuItemImage::create("photo/Daji/Daji1.png", "photo/Daji/Daji1-2.png", "photo/Daji/Daji1-2.png",
			CC_CALLBACK_1(HUDLayer::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Daji/Daji2.png", "photo/Daji/Daji2-2.png", "photo/Daji/Daji2-2.png",
			CC_CALLBACK_1(HUDLayer::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Daji/Daji3.png", "photo/Daji/Daji3-2.png", "photo/Daji/Daji3-2.png",
			CC_CALLBACK_1(HUDLayer::Skill3, this));
	}
	pSkill1Mii->setPosition(70, 150);
	pSkill2Mii->setPosition(120, 90);
	pSkill3Mii->setPosition(70, 30);

	m_pSkillMenu = Menu::create(pSkill1Mii, pSkill2Mii, pSkill3Mii, pAttackMii, pRecoverMii, pCureMii, NULL);
	m_pSkillMenu->setPosition(Vec2::ZERO);
	addChild(m_pSkillMenu, 1);

	scheduleUpdate();
	setKeyboardEnabled(true);	
	return true;
}




void HUDLayer::update(float delta)
{
	///游戏时间更新
	time += delta;
	time_sec = int(time) % 60;
	if (time_sec >= 59)
	{
		number++;
		if (number >= 59)
		{
			time_min++;
			number = 0;
		}
	}

	sprintf(m_textContain, "%d", time_sec);
	m_pTime_secText->setString(m_textContain);

	sprintf(m_textContain, "%d", time_min);
	m_pTime_minText->setString(m_textContain);

	/////技能冷却更新      8   12   18   10   15
	if (!m_Skill1Up)
	{
		m_pSkill1Text->setVisible(true);
		m_pass1 += delta;
		m_Skill1Wait = 8- (int(m_pass1) % 60);
		sprintf(m_textContain, "%d", m_Skill1Wait);
	    m_pSkill1Text->setString(m_textContain);
	}
	if (m_Skill1Wait <= 0)
	{
		m_pass1 = 0;
		m_Skill1Up = true;
		pSkill1Mii->setEnabled(true);
		sprintf(m_textContain, "%d", m_Skill1Wait);
		m_pSkill1Text->setString(m_textContain);
		m_pSkill1Text->setVisible(false);
	}

	if (!m_Skill2Up)
	{
		m_pSkill2Text->setVisible(true);
		m_pass2 += delta;
		m_Skill2Wait = 12 - (int(m_pass2) % 60);
		sprintf(m_textContain, "%d", m_Skill2Wait);
		m_pSkill2Text->setString(m_textContain);
	}
	if (m_Skill2Wait <= 0)
	{
		m_pass2 = 0;
		m_Skill2Up = true;
		pSkill2Mii->setEnabled(true);
		sprintf(m_textContain, "%d", m_Skill2Wait);
		m_pSkill2Text->setString(m_textContain);
		m_pSkill2Text->setVisible(false);
	}

	if (!m_Skill3Up)
	{
		m_pSkill3Text->setVisible(true);
		m_pass3 += delta;
		m_Skill3Wait = 18 - (int(m_pass3) % 60);
		sprintf(m_textContain, "%d", m_Skill3Wait);
		m_pSkill3Text->setString(m_textContain);
	}
	if (m_Skill3Wait <= 0)
	{
		m_pass3 = 0;
		m_Skill3Up = true;
		pSkill3Mii->setEnabled(true);
		sprintf(m_textContain, "%d", m_Skill3Wait);
		m_pSkill3Text->setString(m_textContain);
		m_pSkill3Text->setVisible(false);
	}

	if (!m_Skill4Up)
	{
		m_pSkill4Text->setVisible(true);
		m_pass4 += delta;
		m_Skill4Wait = 10 - (int(m_pass4) % 60);
		sprintf(m_textContain, "%d", m_Skill4Wait);
		m_pSkill4Text->setString(m_textContain);
	}
	if (m_Skill4Wait <= 0)
	{
		m_pass4 = 0;
		m_Skill4Up = true;
		pRecoverMii->setEnabled(true);
		sprintf(m_textContain, "%d", m_Skill4Wait);
		m_pSkill4Text->setString(m_textContain);
		m_pSkill4Text->setVisible(false);
	}

	if (!m_Skill5Up)
	{
		m_pSkill5Text->setVisible(true);
		m_pass5 += delta;
		m_Skill5Wait = 15 - (int(m_pass5) % 60);
		sprintf(m_textContain, "%d", m_Skill5Wait);
		m_pSkill5Text->setString(m_textContain);
	}
	if (m_Skill5Wait <= 0)
	{
		m_pass5 = 0;
		m_Skill5Up = true;
		pCureMii->setEnabled(true);
		sprintf(m_textContain, "%d", m_Skill5Wait);
		m_pSkill5Text->setString(m_textContain);
		m_pSkill5Text->setVisible(false);
	}

	//金钱更新
	if (obj.e_money != e_money)
	{
		e_money = obj.e_money;
		sprintf(m_textContain, "%d", e_money);
		e_pMoney->setString(m_textContain);
	}

	//窗口弹出效果
	if (m_IsPopDialog)
	{
		m_DialogPopTime += delta;
		if (m_DialogPopTime <= 0.3f)
		{
			if (m_DialogPopTime <= 0.2f)
			{
				m_ExitBack->setScale(m_DialogPopTime / 0.2f);
				m_pExitMenu->setScale(m_DialogPopTime / 0.2f);
			}
			else
			{
				if ((m_DialogPopTime - 0.2f) <= 0.05f)
				{
					m_ExitBack->setScale(1.0f + (m_DialogPopTime - 0.2f) / 0.05f*0.3f);
					m_pExitMenu->setScale(1.0f + (m_DialogPopTime - 0.2f) / 0.05f*0.3f);
				}
				else
				{
					m_ExitBack->setScale(1.0f + (1.0f - (m_DialogPopTime - 0.25f) / 0.05f)*0.3f);
					m_pExitMenu->setScale(1.0f + (1.0f - (m_DialogPopTime - 0.25f) / 0.05f)*0.3f);
				}
			}
		}
		else
		{
			m_IsPopDialog = false;
			//m_pExitDialogLayer->setEnable(true);
		}
	}

	
	
}

void HUDLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)    //////键盘事件
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_TAB:
	{
		if (!AttriIsOpen)
		{
			AttriIsOpen = true;
			m_pMenu->setEnabled(false);
			m_pSkillMenu->setEnabled(false);
			m_pMaskImage->setVisible(true);
			m_AttriBack1->setVisible(true);
			m_pAttriMenu->setVisible(true);
			m_pOpAttriMii->setEnabled(false);
			m_pHeroAttriMii->setEnabled(true);
		}
		else if (AttriIsOpen)
		{
			AttriIsOpen = false;
			m_pMenu->setEnabled(true);
			m_pSkillMenu->setEnabled(true);
			m_pMaskImage->setVisible(false);
			m_AttriBack1->setVisible(false);
			m_AttriBack2->setVisible(false);
			m_pAttriMenu->setVisible(false);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_B:
	{
		if (!ShopIsOpen)
		{
			ShopIsOpen = true;
			m_pMenu->setEnabled(false);
			m_pSkillMenu->setEnabled(false);
			m_pMaskImage->setVisible(true);
			m_ShopBack->setVisible(true);
			m_pShopMenu->setVisible(true);
		}
		else if (ShopIsOpen)
		{
			ShopIsOpen = false;
			m_pMenu->setEnabled(true);
			m_pSkillMenu->setEnabled(true);
			m_pMaskImage->setVisible(false);
			m_ShopBack->setVisible(false);
			m_pShopMenu->setVisible(false);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_ENTER:
	{
		if (ExitIsOpen)
		{
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			exit(0);
#endif
		}
    }
	break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
	{
		ExitIsOpen = true;
		m_pMenu->setEnabled(false);
		m_ExitBack->setVisible(true);
		m_pExitMenu->setVisible(true);
		m_ExitBack->setScale(0.0f);
		m_pExitMenu->setScale(0.0f);
		m_pMaskImage->setVisible(true);
		m_IsPopDialog = true;
		m_DialogPopTime = 0.0f;
	}
	}
}


void HUDLayer::openAttri(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_AttriBack1->setVisible(true);
	m_pAttriMenu->setVisible(true);
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
}

void HUDLayer::transToOp(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
	m_AttriBack1->setVisible(true);
	m_AttriBack2->setVisible(false);
}

void HUDLayer::transToHero(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(true);
	m_pHeroAttriMii->setEnabled(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(true);
}

void HUDLayer::closeAttri(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(false);
	m_pAttriMenu->setVisible(false);
}

void HUDLayer::openShop(cocos2d::Ref * pSender)
{
	e_money2 = e_money;
	sprintf(m_textContain, "%d", e_money2);
	e_pMoney2->setString(m_textContain);
	e_pMoney2->setVisible(true);
	m_pRecommandMenu->setVisible(true);
	m_pDownMenu = m_pRecommandMenu;
	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_ShopBack->setVisible(true);
	m_pShopMenu->setVisible(true);
}

void HUDLayer::closeShop(cocos2d::Ref * pSender)
{
	e_pMoney2->setVisible(false);
	m_pDownMenu->setVisible(false);
	m_pMenu->setEnabled(true);
	m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_ShopBack->setVisible(false);
	m_pShopMenu->setVisible(false);
}

void HUDLayer::openExit(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(false);
	m_ExitBack->setVisible(true);
	m_pExitMenu->setVisible(true);
	m_ExitBack->setScale(0.0f);
	m_pExitMenu->setScale(0.0f);
	m_pMaskImage->setVisible(true);
	m_IsPopDialog = true;
	m_DialogPopTime = 0.0f;
}

void HUDLayer::menuYesCallback(cocos2d::Ref * pSender)
{
	TransitionScene * reScene = NULL;
	Scene *pScene = HelloWorld::createScene();
	reScene = TransitionCrossFade::create(0.8f, pScene);
	Director::getInstance()->replaceScene(reScene);
	//m_IsChangeScene = true;
	/*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif*/
}
	


void HUDLayer::menuNoCallback(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_ExitBack->setVisible(false);
	m_pExitMenu->setVisible(false);
	m_pMaskImage->setVisible(false);

}

void HUDLayer::RecommendMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pRecommandMenu->setVisible(true);
	m_pDownMenu = m_pRecommandMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::AttackMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pAttackMenu->setVisible(true);
	m_pDownMenu = m_pAttackMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAttackMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::MagicMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pMagicMenu->setVisible(true);
	m_pDownMenu = m_pMagicMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMagicMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::DefenseMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pDefenseMenu->setVisible(true);
	m_pDownMenu = m_pDefenseMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pDefenseMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::MoveMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pMoveMenu->setVisible(true);
	m_pDownMenu = m_pMoveMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMoveMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::BattleMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pBattleMenu->setVisible(true);
	m_pDownMenu = m_pBattleMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pBattleMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::AssistMenu(cocos2d::Ref * pSender)
{
	m_pDownMenu->setVisible(false);
	m_pAssistMenu->setVisible(true);
	m_pDownMenu = m_pAssistMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAssistMii;
	m_pDownMii->setEnabled(false);
}
///////////////物品函数
void HUDLayer::attack1(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack2(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack3(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack4(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack5(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack6(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack7(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack8(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack9(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack10(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack11(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack12(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack13(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack14(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack15(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack16(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic1(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic2(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic3(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic4(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic5(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic6(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic7(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic8(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic9(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic10(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic11(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic12(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic13(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic14(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic15(cocos2d::Ref * pSender)
{
}

void HUDLayer::magic16(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense1(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense2(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense3(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense4(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense5(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense6(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense7(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense8(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense9(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense10(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense11(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense12(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense13(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense14(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense15(cocos2d::Ref * pSender)
{
}

void HUDLayer::defense16(cocos2d::Ref * pSender)
{
}

void HUDLayer::move1(cocos2d::Ref * pSender)
{
}

void HUDLayer::move2(cocos2d::Ref * pSender)
{
}

void HUDLayer::move3(cocos2d::Ref * pSender)
{
}

void HUDLayer::move4(cocos2d::Ref * pSender)
{
}

void HUDLayer::move5(cocos2d::Ref * pSender)
{
}

void HUDLayer::move6(cocos2d::Ref * pSender)
{
}

void HUDLayer::move7(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle1(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle2(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle3(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle4(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle5(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle6(cocos2d::Ref * pSender)
{
}

void HUDLayer::battle7(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist1(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist2(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist3(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist4(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist5(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist6(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist7(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist8(cocos2d::Ref * pSender)
{
}

void HUDLayer::assist9(cocos2d::Ref * pSender)
{
}

void HUDLayer::attack(cocos2d::Ref* pSender)
{
	//pAttackMii->setEnabled(false);
}

void HUDLayer::recover(cocos2d::Ref* pSender)
{
	m_Skill4Up = false;
	pRecoverMii->setEnabled(false);
}

void HUDLayer::cure(cocos2d::Ref* pSender)
{
	m_Skill5Up = false;
	pCureMii->setEnabled(false);
}

void HUDLayer::Skill1(cocos2d::Ref* pSender)
{
	m_Skill1Up = false;
	pSkill1Mii->setEnabled(false);

}

void HUDLayer::Skill2(cocos2d::Ref* pSender)
{
	m_Skill2Up = false;
	pSkill2Mii->setEnabled(false);
}

void HUDLayer::Skill3(cocos2d::Ref* pSender)
{
	m_Skill3Up = false;
	pSkill3Mii->setEnabled(false);
}



