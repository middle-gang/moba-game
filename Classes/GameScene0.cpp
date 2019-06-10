#include "GameScene0.h"

USING_NS_CC;

Scene* GameScene0::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene0::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene0::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	m_pGameScene2 = GameScene2::create();
	addChild(m_pGameScene2, 0);
	m_pGameScene2->setVisible(true);


	////////////////////////////////英雄属性
	m_kill = m_pGameScene2->Hero.m_kill;
	m_death = m_pGameScene2->Hero.m_death;
	m_level = m_pGameScene2->Hero.Level();
	m_money = m_pGameScene2->Hero.Money();
	t_money = m_pGameScene2->Hero.tMoney();
	

	/////游戏时间
	////游戏时间
	time_min = 0;
	time_sec = 0;
	time = 0;
	number = 0;

	sprintf(m_Textbuffer, "%d", time_min);
	m_pTime_minText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pTime_minText->setPosition(80, 405);
	addChild(m_pTime_minText, 3);

	sprintf(m_Textbuffer, "%d", time_sec);
	m_pTime_secText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
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

	sprintf(m_Textbuffer, "%d", m_Skill1Wait);
	m_pSkill1Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkill1Text->setPosition(80, 145);
	addChild(m_pSkill1Text, 3);
	m_pSkill1Text->setVisible(false);

	sprintf(m_Textbuffer, "%d", m_Skill2Wait);
	m_pSkill2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkill2Text->setPosition(130, 85);
	addChild(m_pSkill2Text, 3);
	m_pSkill2Text->setVisible(false);

	sprintf(m_Textbuffer, "%d", m_Skill3Wait);
	m_pSkill3Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkill3Text->setPosition(80, 25);
	addChild(m_pSkill3Text, 3);
	m_pSkill3Text->setVisible(false);

	sprintf(m_Textbuffer, "%d", m_Skill4Wait);
	m_pSkill4Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkill4Text->setPosition(150, 20);
	addChild(m_pSkill4Text, 3);
	m_pSkill4Text->setVisible(false);

	sprintf(m_Textbuffer, "%d", m_Skill5Wait);
	m_pSkill5Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkill5Text->setPosition(200, 20);
	addChild(m_pSkill5Text, 3);
	m_pSkill5Text->setVisible(false);

	//创建属性1111111界面
	AttriIsOpen = false;
	Sprite *m_pAttriWin = Sprite::create("photo/main/box1.png");
	m_pAttriWin->setPosition(160, 420);
	addChild(m_pAttriWin, 1);

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
		CC_CALLBACK_1(GameScene0::transToOp, this));
	m_pOpAttriMii->setPosition(198, 390);
	m_pOpAttriMii->setEnabled(false);

	m_pHeroAttriMii = MenuItemImage::create("photo/Attribute/heroP_up.png",
		"photo/Attribute/heroP_down.png",
		"photo/Attribute/heroP_down.png",
		CC_CALLBACK_1(GameScene0::transToHero, this));
	m_pHeroAttriMii->setPosition(370, 390);

	m_pCloseAttri = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(GameScene0::closeAttri, this));
	m_pCloseAttri->setPosition(870, 400);

	m_pAttriMenu = Menu::create(m_pOpAttriMii, m_pHeroAttriMii, m_pCloseAttri, NULL);
	m_pAttriMenu->setPosition(Vec2::ZERO);
	addChild(m_pAttriMenu, 12);
	m_pAttriMenu->setVisible(false);


	///////////////////属性11111数值显示
	//窗口
	sprintf(m_Textbuffer, "%d", m_kill);
	m_pKillText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKillText->setPosition(100, 435);
	addChild(m_pKillText, 3);

	m_pKill2Text=Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKill2Text->setColor(Color3B::BLUE);
	m_pKill2Text->setPosition(165,405);
	addChild(m_pKill2Text, 3);

	sprintf(m_Textbuffer, "%d", m_death);
	m_pDeathText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pDeathText->setPosition(150, 435);
	addChild(m_pDeathText, 3);

	Label* m_pAssist = Label::createWithTTF("0", "fonts/msyh.ttc", 23);
	m_pAssist->setPosition(200, 435);
	addChild(m_pAssist, 3);

	////////////////创建属性2222222222222界面
	MenuItemImage *pAttriWin = MenuItemImage::create("photo/Attribute/button.png", "photo/Attribute/button-1.png",
		CC_CALLBACK_1(GameScene0::openAttri2, this));
	pAttriWin->setPosition(930, 150);

	m_AttriB1 = Sprite::create("photo/Attribute/attriB1.png");
	m_AttriB1->setPosition(500, 236.5);
	addChild(m_AttriB1, 11);
	m_AttriB1->setVisible(false);

	m_AttriB2 = Sprite::create("photo/Attribute/attriB2.png");
	m_AttriB2->setPosition(500, 236.5);
	addChild(m_AttriB2, 11);
	m_AttriB2->setVisible(false);

	m_button1 = MenuItemImage::create("photo/Attribute/button1.png",
		"photo/Attribute/button1-1.png",
		"photo/Attribute/button1-1.png",
		CC_CALLBACK_1(GameScene0::transTo1, this));
	m_button1->setPosition(166,328);
	m_button1->setEnabled(false);

	m_button2 = MenuItemImage::create("photo/Attribute/button2.png",
		"photo/Attribute/button2-1.png",
		"photo/Attribute/button2-1.png",
		CC_CALLBACK_1(GameScene0::transTo2, this));
	m_button2->setPosition(166,286);

	m_closebutton = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(GameScene0::closeAttri2, this));
	m_closebutton->setPosition(870, 400);

	m_AttriMenu = Menu::create(m_button1, m_button2, m_closebutton, NULL);
	m_AttriMenu->setPosition(Vec2::ZERO);
	addChild(m_AttriMenu, 12);
	m_AttriMenu->setVisible(false);

	/////////////////////////////创建商店界面
	ShopIsOpen = false;
	MenuItemImage * pShopWin = MenuItemImage::create("photo/shop.png", "photo/shop1.png",
		CC_CALLBACK_1(GameScene0::openShop, this));
	pShopWin->setPosition(930, 200);

	//////金钱显示
	sprintf(m_Textbuffer, "%d", m_money);
	m_pMoneyText= Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 15);
	m_pMoneyText->setColor(Color3B::BLACK);
	m_pMoneyText->setPosition(928, 189);
	addChild(m_pMoneyText, 3);

	m_pMoney2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pMoney2Text->setColor(Color3B::BLUE);
	m_pMoney2Text->setPosition(180, 375);
	m_pMoney2Text->setVisible(false);
	addChild(m_pMoney2Text, 13);

	t_pMoneyText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	t_pMoneyText->setColor(Color3B::BLACK);
	t_pMoneyText->setPosition(430, 325);
	t_pMoneyText->setVisible(false);
	addChild(t_pMoneyText, 13);

	t_pMoney2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	t_pMoney2Text->setColor(Color3B::BLACK);
	t_pMoney2Text->setPosition(487, 288);
	t_pMoney2Text->setVisible(false);
	addChild(t_pMoney2Text, 13);

	//商店背景
	m_ShopBack = Sprite::create("photo/shop/background.png");
	m_ShopBack->setPosition(500, 236.5);
	addChild(m_ShopBack, 11);
	m_ShopBack->setVisible(false);

	/////////////////////////////////////////////////////////////////////////////////商店物品

	memset(&s_Equip, 0, sizeof(s_Equip));
	//////////////////////////////////////////////////////按钮
	////推荐
	m_pRecomBac = Sprite::create("photo/shop/recomB.png");
	m_pRecomBac->setPosition(503, 225);
	addChild(m_pRecomBac, 14);
	m_pRecomBac->setVisible(false);

	s_Equip[0][0].pMenuItemImage = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[0][1].pMenuItemImage = MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[0][2].pMenuItemImage = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[0][3].pMenuItemImage = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[0][4].pMenuItemImage = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 3;i++)
	{
		s_Equip[0][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		s_Equip[0][i].pMenuItemImage->setEnabled(false); 
	}
	s_Equip[0][4].pMenuItemImage->setPosition(270, 285);
	s_Equip[0][4].pMenuItemImage->setEnabled(false);

	m_pRecommandMenu = Menu::create(s_Equip[0][0].pMenuItemImage, s_Equip[0][1].pMenuItemImage, s_Equip[0][2].pMenuItemImage, s_Equip[0][3].pMenuItemImage,
		s_Equip[0][4].pMenuItemImage, NULL);
	m_pRecommandMenu->setPosition(Vec2::ZERO);
	addChild(m_pRecommandMenu, 13);
	m_pRecommandMenu->setVisible(false);

	/////攻击
	m_pAttackBac= Sprite::create("photo/shop/attackB.png");
	m_pAttackBac->setPosition(503, 225);
	addChild(m_pAttackBac, 14);
	m_pAttackBac->setVisible(false);

	s_Equip[1][0].pMenuItemImage = MenuItemImage::create("photo/shop/attack/1.jpg",
		"photo/shop/attack/1_1.jpg",
		"photo/shop/attack/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][1].pMenuItemImage = MenuItemImage::create("photo/shop/attack/2.jpg",
		"photo/shop/attack/2_1.jpg",
		"photo/shop/attack/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][2].pMenuItemImage = MenuItemImage::create("photo/shop/attack/3.jpg",
		"photo/shop/attack/3_1.jpg",
		"photo/shop/attack/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][3].pMenuItemImage = MenuItemImage::create("photo/shop/attack/4.jpg",
		"photo/shop/attack/4_1.jpg",
		"photo/shop/attack/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][4].pMenuItemImage = MenuItemImage::create("photo/shop/attack/5.jpg",
		"photo/shop/attack/5_1.jpg",
		"photo/shop/attack/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][5].pMenuItemImage = MenuItemImage::create("photo/shop/attack/6.jpg",
		"photo/shop/attack/6_1.jpg",
		"photo/shop/attack/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][6].pMenuItemImage = MenuItemImage::create("photo/shop/attack/7.jpg",
		"photo/shop/attack/7_1.jpg",
		"photo/shop/attack/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][7].pMenuItemImage = MenuItemImage::create("photo/shop/attack/8.jpg",
		"photo/shop/attack/8_1.jpg",
		"photo/shop/attack/8_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][8].pMenuItemImage = MenuItemImage::create("photo/shop/attack/9.jpg",
		"photo/shop/attack/9_1.jpg",
		"photo/shop/attack/9_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][9].pMenuItemImage = MenuItemImage::create("photo/shop/attack/10.jpg",
		"photo/shop/attack/10_1.jpg",
		"photo/shop/attack/10_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][10].pMenuItemImage = MenuItemImage::create("photo/shop/attack/11.jpg",
		"photo/shop/attack/11_1.jpg",
		"photo/shop/attack/11_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][11].pMenuItemImage = MenuItemImage::create("photo/shop/attack/12.jpg",
		"photo/shop/attack/12_1.jpg",
		"photo/shop/attack/12_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][12].pMenuItemImage = MenuItemImage::create("photo/shop/attack/13.jpg",
		"photo/shop/attack/13_1.jpg",
		"photo/shop/attack/13_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][13].pMenuItemImage = MenuItemImage::create("photo/shop/attack/14.jpg",
		"photo/shop/attack/14_1.jpg",
		"photo/shop/attack/14_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][14].pMenuItemImage = MenuItemImage::create("photo/shop/attack/15.jpg",
		"photo/shop/attack/15_1.jpg",
		"photo/shop/attack/15_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[1][15].pMenuItemImage = MenuItemImage::create("photo/shop/attack/16.jpg",
		"photo/shop/attack/16_1.jpg",
		"photo/shop/attack/16_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 15; i++)
	{
		s_Equip[1][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[1][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[1][i].pMenuItemImage->setPosition(270 + (i%4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pAttackMenu = Menu::create(s_Equip[1][0].pMenuItemImage, s_Equip[1][1].pMenuItemImage, s_Equip[1][2].pMenuItemImage, s_Equip[1][3].pMenuItemImage,
		s_Equip[1][4].pMenuItemImage, s_Equip[1][5].pMenuItemImage, s_Equip[1][6].pMenuItemImage, s_Equip[1][7].pMenuItemImage,
		s_Equip[1][8].pMenuItemImage, s_Equip[1][9].pMenuItemImage, s_Equip[1][10].pMenuItemImage, s_Equip[1][11].pMenuItemImage,
		s_Equip[1][12].pMenuItemImage, s_Equip[1][13].pMenuItemImage, s_Equip[1][14].pMenuItemImage, s_Equip[1][15].pMenuItemImage, NULL);
	m_pAttackMenu->setPosition(Vec2::ZERO);
	addChild(m_pAttackMenu, 13);
	m_pAttackMenu->setVisible(false);

	//法术
	m_pMagicBac= Sprite::create("photo/shop/magicB.png");
	m_pMagicBac->setPosition(503, 225);
	addChild(m_pMagicBac, 14);
	m_pMagicBac->setVisible(false);

	s_Equip[2][0].pMenuItemImage = MenuItemImage::create("photo/shop/magic/1.jpg",
		"photo/shop/magic/1_1.jpg",
		"photo/shop/magic/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][1].pMenuItemImage = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][2].pMenuItemImage = MenuItemImage::create("photo/shop/magic/3.jpg",
		"photo/shop/magic/3_1.jpg",
		"photo/shop/magic/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][3].pMenuItemImage = MenuItemImage::create("photo/shop/magic/4.jpg",
		"photo/shop/magic/4_1.jpg",
		"photo/shop/magic/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][4].pMenuItemImage = MenuItemImage::create("photo/shop/magic/5.jpg",
		"photo/shop/magic/5_1.jpg",
		"photo/shop/magic/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][5].pMenuItemImage = MenuItemImage::create("photo/shop/magic/6.jpg",
		"photo/shop/magic/6_1.jpg",
		"photo/shop/magic/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][6].pMenuItemImage = MenuItemImage::create("photo/shop/magic/7.jpg",
		"photo/shop/magic/7_1.jpg",
		"photo/shop/magic/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][7].pMenuItemImage = MenuItemImage::create("photo/shop/magic/8.jpg",
		"photo/shop/magic/8_1.jpg",
		"photo/shop/magic/8_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][8].pMenuItemImage = MenuItemImage::create("photo/shop/magic/9.jpg",
		"photo/shop/magic/9_1.jpg",
		"photo/shop/magic/9_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][9].pMenuItemImage = MenuItemImage::create("photo/shop/magic/10.jpg",
		"photo/shop/magic/10_1.jpg",
		"photo/shop/magic/10_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][10].pMenuItemImage = MenuItemImage::create("photo/shop/magic/11.jpg",
		"photo/shop/magic/11_1.jpg",
		"photo/shop/magic/11_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][11].pMenuItemImage = MenuItemImage::create("photo/shop/magic/12.jpg",
		"photo/shop/magic/12_1.jpg",
		"photo/shop/magic/12_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][12].pMenuItemImage = MenuItemImage::create("photo/shop/magic/13.jpg",
		"photo/shop/magic/13_1.jpg",
		"photo/shop/magic/13_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][13].pMenuItemImage = MenuItemImage::create("photo/shop/magic/14.jpg",
		"photo/shop/magic/14_1.jpg",
		"photo/shop/magic/14_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][14].pMenuItemImage = MenuItemImage::create("photo/shop/magic/15.jpg",
		"photo/shop/magic/15_1.jpg",
		"photo/shop/magic/15_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[2][15].pMenuItemImage = MenuItemImage::create("photo/shop/magic/16.jpg",
		"photo/shop/magic/16_1.jpg",
		"photo/shop/magic/16_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 15; i++)
	{
		s_Equip[2][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[2][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[2][i].pMenuItemImage->setPosition(270 + (i%4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pMagicMenu = Menu::create(s_Equip[2][0].pMenuItemImage, s_Equip[2][1].pMenuItemImage, s_Equip[2][2].pMenuItemImage, s_Equip[2][3].pMenuItemImage,
		s_Equip[2][4].pMenuItemImage, s_Equip[2][5].pMenuItemImage, s_Equip[2][6].pMenuItemImage, s_Equip[2][7].pMenuItemImage,
		s_Equip[2][8].pMenuItemImage, s_Equip[2][9].pMenuItemImage, s_Equip[2][10].pMenuItemImage, s_Equip[2][11].pMenuItemImage,
		s_Equip[2][12].pMenuItemImage, s_Equip[2][13].pMenuItemImage, s_Equip[2][14].pMenuItemImage, s_Equip[2][15].pMenuItemImage, NULL);
	m_pMagicMenu->setPosition(Vec2::ZERO);
	addChild(m_pMagicMenu, 13);
	m_pMagicMenu->setVisible(false);

	///防御
	m_pDefenseBac = Sprite::create("photo/shop/defenseB.png");
	m_pDefenseBac->setPosition(503, 225);
	addChild(m_pDefenseBac, 14);
	m_pDefenseBac->setVisible(false);

	s_Equip[3][0].pMenuItemImage = MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][1].pMenuItemImage = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][2].pMenuItemImage = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][3].pMenuItemImage = MenuItemImage::create("photo/shop/defense/4.jpg",
		"photo/shop/defense/4_1.jpg",
		"photo/shop/defense/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][4].pMenuItemImage = MenuItemImage::create("photo/shop/defense/5.jpg",
		"photo/shop/defense/5_1.jpg",
		"photo/shop/defense/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][5].pMenuItemImage = MenuItemImage::create("photo/shop/defense/6.jpg",
		"photo/shop/defense/6_1.jpg",
		"photo/shop/defense/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][6].pMenuItemImage = MenuItemImage::create("photo/shop/defense/7.jpg",
		"photo/shop/defense/7_1.jpg",
		"photo/shop/defense/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][7].pMenuItemImage = MenuItemImage::create("photo/shop/defense/8.jpg",
		"photo/shop/defense/8_1.jpg",
		"photo/shop/defense/8_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][8].pMenuItemImage = MenuItemImage::create("photo/shop/defense/9.jpg",
		"photo/shop/defense/9_1.jpg",
		"photo/shop/defense/9_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][9].pMenuItemImage = MenuItemImage::create("photo/shop/defense/10.jpg",
		"photo/shop/defense/10_1.jpg",
		"photo/shop/defense/10_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][10].pMenuItemImage = MenuItemImage::create("photo/shop/defense/11.jpg",
		"photo/shop/defense/11_1.jpg",
		"photo/shop/defense/11_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][11].pMenuItemImage = MenuItemImage::create("photo/shop/defense/12.jpg",
		"photo/shop/defense/12_1.jpg",
		"photo/shop/defense/12_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][12].pMenuItemImage = MenuItemImage::create("photo/shop/defense/13.jpg",
		"photo/shop/defense/13_1.jpg",
		"photo/shop/defense/13_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][13].pMenuItemImage = MenuItemImage::create("photo/shop/defense/14.jpg",
		"photo/shop/defense/14_1.jpg",
		"photo/shop/defense/14_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][14].pMenuItemImage = MenuItemImage::create("photo/shop/defense/15.jpg",
		"photo/shop/defense/15_1.jpg",
		"photo/shop/defense/15_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[3][15].pMenuItemImage = MenuItemImage::create("photo/shop/defense/16.jpg",
		"photo/shop/defense/16_1.jpg",
		"photo/shop/defense/16_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 15; i++)
	{
		s_Equip[3][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[3][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[3][i].pMenuItemImage->setPosition(270 + (i%4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pDefenseMenu = Menu::create(s_Equip[3][0].pMenuItemImage, s_Equip[3][1].pMenuItemImage, s_Equip[3][2].pMenuItemImage, s_Equip[3][3].pMenuItemImage,
		s_Equip[3][4].pMenuItemImage, s_Equip[3][5].pMenuItemImage, s_Equip[3][6].pMenuItemImage, s_Equip[3][7].pMenuItemImage,
		s_Equip[3][8].pMenuItemImage, s_Equip[3][9].pMenuItemImage, s_Equip[3][10].pMenuItemImage, s_Equip[3][11].pMenuItemImage,
		s_Equip[3][12].pMenuItemImage, s_Equip[3][13].pMenuItemImage, s_Equip[3][14].pMenuItemImage, s_Equip[3][15].pMenuItemImage, NULL);
	m_pDefenseMenu->setPosition(Vec2::ZERO);
	addChild(m_pDefenseMenu, 13);
	m_pDefenseMenu->setVisible(false);

	///移动
	m_pMoveBac = Sprite::create("photo/shop/moveB.png");
	m_pMoveBac->setPosition(503, 225);
	addChild(m_pMoveBac, 14);
	m_pMoveBac->setVisible(false);

	s_Equip[4][0].pMenuItemImage = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][1].pMenuItemImage = MenuItemImage::create("photo/shop/move/2.jpg",
		"photo/shop/move/2_1.jpg",
		"photo/shop/move/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][2].pMenuItemImage = MenuItemImage::create("photo/shop/move/3.jpg",
		"photo/shop/move/3_1.jpg",
		"photo/shop/move/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][3].pMenuItemImage = MenuItemImage::create("photo/shop/move/4.jpg",
		"photo/shop/move/4_1.jpg",
		"photo/shop/move/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][4].pMenuItemImage = MenuItemImage::create("photo/shop/move/5.jpg",
		"photo/shop/move/5_1.jpg",
		"photo/shop/move/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][5].pMenuItemImage = MenuItemImage::create("photo/shop/move/6.jpg",
		"photo/shop/move/6_1.jpg",
		"photo/shop/move/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[4][6].pMenuItemImage = MenuItemImage::create("photo/shop/move/7.jpg",
		"photo/shop/move/7_1.jpg",
		"photo/shop/move/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 6; i++)
	{
		s_Equip[4][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[4][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[4][i].pMenuItemImage->setPosition(270 + (i % 4) * 120, 370 - (i / 4) * 85);
		}
	}
	m_pMoveMenu = Menu::create(s_Equip[4][0].pMenuItemImage, s_Equip[4][1].pMenuItemImage, s_Equip[4][2].pMenuItemImage, s_Equip[4][3].pMenuItemImage,
		s_Equip[4][4].pMenuItemImage, s_Equip[4][5].pMenuItemImage, s_Equip[4][6].pMenuItemImage, NULL);
	m_pMoveMenu->setPosition(Vec2::ZERO);
	addChild(m_pMoveMenu, 13);
	m_pMoveMenu->setVisible(false);

	///打野
	m_pBattleBac = Sprite::create("photo/shop/battleB.png");
	m_pBattleBac->setPosition(503, 225);
	addChild(m_pBattleBac, 14);
	m_pBattleBac->setVisible(false);

	s_Equip[5][0].pMenuItemImage = MenuItemImage::create("photo/shop/battle/1.jpg",
		"photo/shop/battle/1_1.jpg",
		"photo/shop/battle/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][1].pMenuItemImage = MenuItemImage::create("photo/shop/battle/2.jpg",
		"photo/shop/battle/2_1.jpg",
		"photo/shop/battle/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][2].pMenuItemImage = MenuItemImage::create("photo/shop/battle/3.jpg",
		"photo/shop/battle/3_1.jpg",
		"photo/shop/battle/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][3].pMenuItemImage = MenuItemImage::create("photo/shop/battle/4.jpg",
		"photo/shop/battle/4_1.jpg",
		"photo/shop/battle/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][4].pMenuItemImage = MenuItemImage::create("photo/shop/battle/5.jpg",
		"photo/shop/battle/5_1.jpg",
		"photo/shop/battle/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][5].pMenuItemImage = MenuItemImage::create("photo/shop/battle/6.jpg",
		"photo/shop/battle/6_1.jpg",
		"photo/shop/battle/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[5][6].pMenuItemImage = MenuItemImage::create("photo/shop/battle/7.jpg",
		"photo/shop/battle/7_1.jpg",
		"photo/shop/battle/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));

	for (int i = 0; i <= 6; i++)
	{
		s_Equip[5][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[5][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[5][i].pMenuItemImage->setPosition(270 + (i%4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pBattleMenu = Menu::create(s_Equip[5][0].pMenuItemImage, s_Equip[5][1].pMenuItemImage, s_Equip[5][2].pMenuItemImage, s_Equip[5][3].pMenuItemImage,
		s_Equip[5][4].pMenuItemImage, s_Equip[5][5].pMenuItemImage, s_Equip[5][6].pMenuItemImage, NULL);
	m_pBattleMenu->setPosition(Vec2::ZERO);
	addChild(m_pBattleMenu, 13);
	m_pBattleMenu->setVisible(false);

	///辅助
	m_pAssistBac = Sprite::create("photo/shop/assistB.png");
	m_pAssistBac->setPosition(503, 225);
	addChild(m_pAssistBac, 14);
	m_pAssistBac->setVisible(false);

	s_Equip[6][0].pMenuItemImage = MenuItemImage::create("photo/shop/assist/1.jpg",
		"photo/shop/assist/1_1.jpg",
		"photo/shop/assist/1_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][1].pMenuItemImage = MenuItemImage::create("photo/shop/assist/2.jpg",
		"photo/shop/assist/2_1.jpg",
		"photo/shop/assist/2_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][2].pMenuItemImage = MenuItemImage::create("photo/shop/assist/3.jpg",
		"photo/shop/assist/3_1.jpg",
		"photo/shop/assist/3_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][3].pMenuItemImage = MenuItemImage::create("photo/shop/assist/4.jpg",
		"photo/shop/assist/4_1.jpg",
		"photo/shop/assist/4_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][4].pMenuItemImage = MenuItemImage::create("photo/shop/assist/5.jpg",
		"photo/shop/assist/5_1.jpg",
		"photo/shop/assist/5_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][5].pMenuItemImage = MenuItemImage::create("photo/shop/assist/6.jpg",
		"photo/shop/assist/6_1.jpg",
		"photo/shop/assist/6_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][6].pMenuItemImage = MenuItemImage::create("photo/shop/assist/7.jpg",
		"photo/shop/assist/7_1.jpg",
		"photo/shop/assist/7_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][7].pMenuItemImage = MenuItemImage::create("photo/shop/assist/8.jpg",
		"photo/shop/assist/8_1.jpg",
		"photo/shop/assist/8_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	s_Equip[6][8].pMenuItemImage = MenuItemImage::create("photo/shop/assist/9.jpg",
		"photo/shop/assist/9_1.jpg",
		"photo/shop/assist/9_1.jpg",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	for (int i = 0; i <= 8; i++)
	{
		s_Equip[6][i].pMenuItemImage->setEnabled(false);
		if (i <= 3)
		{
			s_Equip[6][i].pMenuItemImage->setPosition(270 + i * 120, 370);
		}
		else //if(i<=7)
		{
			s_Equip[6][i].pMenuItemImage->setPosition(270 + (i % 4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pAssistMenu = Menu::create(s_Equip[6][0].pMenuItemImage, s_Equip[6][1].pMenuItemImage, s_Equip[6][2].pMenuItemImage, s_Equip[6][3].pMenuItemImage,
		s_Equip[6][4].pMenuItemImage, s_Equip[6][5].pMenuItemImage, s_Equip[6][6].pMenuItemImage, s_Equip[6][7].pMenuItemImage,
		s_Equip[6][8].pMenuItemImage, NULL);
	m_pAssistMenu->setPosition(Vec2::ZERO);
	addChild(m_pAssistMenu, 13);
	m_pAssistMenu->setVisible(false);

	////////////////////////////////////////属性
	////////////////攻击
	//属性
	s_Equip[1][0].attack = 20;
	s_Equip[1][1].attackingSpeed = m_pGameScene2->Hero.AttackSpeed()*0.1;
	s_Equip[1][2].damageChance = 0.08;
	s_Equip[1][3].attack = m_pGameScene2->Hero.AttackPower()*0.1;
	s_Equip[1][3].physicBloodSuck = m_pGameScene2->Hero.PhysicBloodSuck()*0.8;
	s_Equip[1][4].attack = 40;
	s_Equip[1][5].damageChance = 0.15;
	s_Equip[1][6].attack = 80;
	s_Equip[1][7].attack = 40;
	s_Equip[1][7].health = 300;
	s_Equip[1][8].attackingSpeed = m_pGameScene2->Hero.AttackSpeed()*0.15;
	s_Equip[1][8].damageChance = 0.1;
	s_Equip[1][8].velocity = m_pGameScene2->Hero.getVelocity()*0.05;
	s_Equip[1][9].attack = m_pGameScene2->Hero.AttackPower()*0.45;
	s_Equip[1][9].waitLessen = 0.1;
	s_Equip[1][9].armorIgnore = 60;
	s_Equip[1][9].magicdenfenceIgnore = 60;
	s_Equip[1][10].attack = 80;
	s_Equip[1][10].waitLessen = 0.1;
	s_Equip[1][10].armorIgnore = 0.4;
	s_Equip[1][11].attack = 60;
	s_Equip[1][11].attackingSpeed = m_pGameScene2->Hero.AttackSpeed()*0.3;
	s_Equip[1][11].physicBloodSuck = 0.1;
	s_Equip[1][12].attack = 60;
	s_Equip[1][12].waitLessen = 0.05;
	s_Equip[1][13].attack = 80;
	s_Equip[1][13].health = 600;
	s_Equip[1][14].attackingSpeed = m_pGameScene2->Hero.AttackSpeed()*0.25;
	if (myChoice == 2)
	{
		s_Equip[1][14].attack = 30;
		s_Equip[1][14].power = 30;
	}
	else
	{
		s_Equip[1][14].attack = 60;
		s_Equip[1][14].power = 60;
	}
	s_Equip[1][15].attack = 100;
	s_Equip[1][15].magicBloodSuck = 0.1;

	//金钱
	s_Equip[1][0].buymoney = 250;     s_Equip[1][0].sellmoney = 150;
	s_Equip[1][1].buymoney = 290;     s_Equip[1][1].sellmoney = 174;
	s_Equip[1][2].buymoney = 320;     s_Equip[1][2].sellmoney = 192;
	s_Equip[1][3].buymoney = 410;     s_Equip[1][3].sellmoney = 246;
	s_Equip[1][4].buymoney = 450;     s_Equip[1][4].sellmoney = 270;
	s_Equip[1][5].buymoney = 550;     s_Equip[1][5].sellmoney = 330;
	s_Equip[1][6].buymoney = 910;     s_Equip[1][6].sellmoney = 546;
	s_Equip[1][7].buymoney = 790;     s_Equip[1][7].sellmoney = 474;
	s_Equip[1][8].buymoney = 890;     s_Equip[1][8].sellmoney = 534;
	s_Equip[1][9].buymoney = 1048;     s_Equip[1][9].sellmoney = 648;
	s_Equip[1][10].buymoney = 2100;     s_Equip[1][10].sellmoney = 1260;
	s_Equip[1][11].buymoney = 2160;     s_Equip[1][11].sellmoney = 1296;
	s_Equip[1][12].buymoney = 1760;     s_Equip[1][12].sellmoney = 1056;
	s_Equip[1][13].buymoney = 1980;     s_Equip[1][13].sellmoney = 1188;
	s_Equip[1][14].buymoney = 890;     s_Equip[1][14].sellmoney = 534;
	s_Equip[1][15].buymoney = 1800;     s_Equip[1][15].sellmoney = 1080;
	
	///////////////////法术
	//属性
	s_Equip[2][0].power = 40;
	s_Equip[2][1].magicpoint = 300;
	s_Equip[2][2].magicpointRecover = 10;
	s_Equip[2][3].power = 20;
	s_Equip[2][3].waitLessen = 0.08;
	s_Equip[2][4].power = 80;
	s_Equip[2][5].power = 120;
	s_Equip[2][6].power = 80;
	s_Equip[2][6].magicBloodSuck = 20;
	s_Equip[2][6].waitLessen = 0.05;
	s_Equip[2][7].health = 400;
	s_Equip[2][7].power = 400;
	s_Equip[2][8].power = 70;
	s_Equip[2][8].health = 300;
	s_Equip[2][8].magicdenfenceIgnore = 75;
	s_Equip[2][9].health = 400;
	s_Equip[2][9].power = 400;
	s_Equip[2][10].power = 75;
	s_Equip[2][10].waitLessen = 0.1;
	s_Equip[2][10].magicBloodSuck = 0.2;
	s_Equip[2][11].power = 180;
	s_Equip[2][11].magicpoint = 600;
	s_Equip[2][11].magicpointRecover = 15;
	s_Equip[2][12].power = 240;
	s_Equip[2][12].velocity = m_pGameScene2->Hero.getVelocity()*0.05;
	s_Equip[2][13].power = 240;
	s_Equip[2][13].health = 300;
	s_Equip[2][13].magicdenfenceIgnore = m_pGameScene2->Hero.E_MagicDenfense()*0.45;
	s_Equip[2][14].power = 240 + (m_pGameScene2->Hero.Power() + 240)*0.35;
	s_Equip[2][15].power = 160;
	s_Equip[2][15].waitLessen = 0.1;
	//金钱
	s_Equip[2][0].buymoney = 300;     s_Equip[2][0].sellmoney = 180;
	s_Equip[2][1].buymoney = 220;     s_Equip[2][1].sellmoney = 132;
	s_Equip[2][2].buymoney = 120;     s_Equip[2][2].sellmoney = 72;
	s_Equip[2][3].buymoney = 500;     s_Equip[2][3].sellmoney = 300;
	s_Equip[2][4].buymoney = 540;     s_Equip[2][4].sellmoney = 324;
	s_Equip[2][5].buymoney = 820;     s_Equip[2][5].sellmoney = 492;
	s_Equip[2][6].buymoney = 800;     s_Equip[2][6].sellmoney = 480;
	s_Equip[2][7].buymoney = 730;     s_Equip[2][7].sellmoney = 438;
	s_Equip[2][8].buymoney = 1020;     s_Equip[2][8].sellmoney = 612;
	s_Equip[2][9].buymoney = 720;     s_Equip[2][9].sellmoney = 432;
	s_Equip[2][10].buymoney = 1240;     s_Equip[2][10].sellmoney = 744;
	s_Equip[2][11].buymoney = 1950;     s_Equip[2][11].sellmoney = 1170;
	s_Equip[2][12].buymoney = 2050;     s_Equip[2][12].sellmoney = 1230;
	s_Equip[2][13].buymoney = 2110;     s_Equip[2][13].sellmoney = 1266;
	s_Equip[2][14].buymoney = 2300;     s_Equip[2][14].sellmoney = 1380;
	s_Equip[2][15].buymoney = 1990;     s_Equip[2][15].sellmoney = 1194;

	//////////////////防御
	s_Equip[3][0].health = 300;
	s_Equip[3][1].armor = 90;
	s_Equip[3][2].magicDenfence = 90;
	s_Equip[3][3].magicpointRecover = 30;
	s_Equip[3][4].health = 1000;
	s_Equip[3][5].health = 700;
	s_Equip[3][6].magicDenfence = 120;
	s_Equip[3][6].health = 700;
	s_Equip[3][6].healthRecover = 50;
	s_Equip[3][7].waitLessen = 0.1;
	s_Equip[3][7].magicpoint = 400;
	s_Equip[3][7].armor = 110;
	s_Equip[3][8].armor = 210;
	s_Equip[3][9].attack = 40;
	s_Equip[3][9].armor = 420;
	s_Equip[3][10].attack = 20;
	s_Equip[3][10].health = 1000;
	s_Equip[3][11].armor = 240;
	s_Equip[3][11].health = 1000;
	s_Equip[3][12].health = 2000;
	s_Equip[3][13].armor = 270;
	s_Equip[3][13].health = 1200;
	s_Equip[3][14].healthRecover = 100;
	s_Equip[3][14].magicDenfence = 240;
	s_Equip[3][14].health = 1200;
	s_Equip[3][15].magicDenfence = 360;
	s_Equip[3][15].health = 1000;

	//金钱
	s_Equip[3][0].buymoney = 300;     s_Equip[3][0].sellmoney = 180;
	s_Equip[3][1].buymoney = 220;     s_Equip[3][1].sellmoney = 132;
	s_Equip[3][2].buymoney = 220;     s_Equip[3][2].sellmoney = 132;
	s_Equip[3][3].buymoney = 140;     s_Equip[3][3].sellmoney = 84;
	s_Equip[3][4].buymoney = 900;     s_Equip[3][4].sellmoney = 540;
	s_Equip[3][5].buymoney = 900;     s_Equip[3][5].sellmoney = 540;
	s_Equip[3][6].buymoney = 1020;     s_Equip[3][6].sellmoney = 612;
	s_Equip[3][7].buymoney = 900;     s_Equip[3][7].sellmoney = 540;
	s_Equip[3][8].buymoney = 730;     s_Equip[3][8].sellmoney = 438;
	s_Equip[3][9].buymoney = 1840;     s_Equip[3][9].sellmoney = 1104;
	s_Equip[3][10].buymoney = 2120;     s_Equip[3][10].sellmoney = 1272;
	s_Equip[3][11].buymoney = 1830;     s_Equip[3][11].sellmoney = 1098;
	s_Equip[3][12].buymoney = 2070;     s_Equip[3][12].sellmoney = 1242;
	s_Equip[3][13].buymoney = 2180;     s_Equip[3][13].sellmoney = 1308;
	s_Equip[3][14].buymoney = 2100;     s_Equip[3][14].sellmoney = 1260;
	s_Equip[3][15].buymoney = 2120;     s_Equip[3][15].sellmoney = 1272;

	//////////////////移动
	s_Equip[4][0].velocity = 30;
	s_Equip[4][1].armor = 110;
	s_Equip[4][1].velocity = 60;
	s_Equip[4][2].magicDenfence = 110;
	s_Equip[4][3].waitLessen = 0.15;
	s_Equip[4][4].magicpointRecover = 25;
	s_Equip[4][4].velocity = 60;
	s_Equip[4][4].magicdenfenceIgnore = 75;
	s_Equip[4][5].velocity = 60;
	s_Equip[4][5].attackingSpeed = m_pGameScene2->Hero.AttackSpeed()*0.3;
	s_Equip[4][6].velocity = 60;

	//金钱
	s_Equip[4][0].buymoney = 250;     s_Equip[4][0].sellmoney = 150;
	s_Equip[4][1].buymoney = 710;     s_Equip[4][1].sellmoney = 426;
	s_Equip[4][2].buymoney = 710;     s_Equip[4][2].sellmoney = 426;
	s_Equip[4][3].buymoney = 710;     s_Equip[4][3].sellmoney = 426;
	s_Equip[4][4].buymoney = 710;     s_Equip[4][4].sellmoney = 426;
	s_Equip[4][5].buymoney = 710;     s_Equip[4][5].sellmoney = 426;
	s_Equip[4][6].buymoney = 530;     s_Equip[4][6].sellmoney = 318;

	//////////////////打野
	//////////////////辅助




	////切换按键
	m_pRecomMii = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	m_pRecomMii->setPosition(166, 328);

	m_pAttackMii = MenuItemImage::create("photo/shop/attack.png",
		"photo/shop/attack1.png",
		"photo/shop/attack1.png",
		CC_CALLBACK_1(GameScene0::AttackMenu, this));
	m_pAttackMii->setPosition(166, 286);

	m_pMagicMii = MenuItemImage::create("photo/shop/Magic.png",
		"photo/shop/Magic1.png",
		"photo/shop/Magic1.png",
		CC_CALLBACK_1(GameScene0::MagicMenu, this));
	m_pMagicMii->setPosition(166, 244);

	m_pDefenseMii = MenuItemImage::create("photo/shop/defense.png",
		"photo/shop/defense1.png",
		"photo/shop/defense1.png",
		CC_CALLBACK_1(GameScene0::DefenseMenu, this));
	m_pDefenseMii->setPosition(166, 202);

	m_pMoveMii = MenuItemImage::create("photo/shop/move.png",
		"photo/shop/move1.png",
		"photo/shop/move1.png",
		CC_CALLBACK_1(GameScene0::MoveMenu, this));
	m_pMoveMii->setPosition(166, 160);

	m_pBattleMii = MenuItemImage::create("photo/shop/battle.png",
		"photo/shop/battle1.png",
		"photo/shop/battle1.png",
		CC_CALLBACK_1(GameScene0::BattleMenu, this));
	m_pBattleMii->setPosition(166, 118);

	m_pAssistMii = MenuItemImage::create("photo/shop/assist.png",
		"photo/shop/assist1.png",
		"photo/shop/assist1.png",
		CC_CALLBACK_1(GameScene0::AssistMenu, this));
	m_pAssistMii->setPosition(166, 76);

	//记录按下去的
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
	//////关闭按钮
	m_pCloseShop = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(GameScene0::closeShop, this));
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
		CC_CALLBACK_1(GameScene0::openExit, this));
	pExitWin->setPosition(Vec2(origin.x + visibleSize.width - pExitWin->getContentSize().width / 2.0f, origin.y + visibleSize.height - pExitWin->getContentSize().height / 2.0f));

	m_ExitBack = Sprite::create("image/gamescene/exit_dialog.png");
	m_ExitBack->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
	addChild(m_ExitBack, 15);
	m_ExitBack->setVisible(false);

	m_pYesMii = MenuItemImage::create("image/gamescene/yes_btn_up.png", "image/gamescene/yes_btn_down.png",
		CC_CALLBACK_1(GameScene0::menuYesCallback, this));
	m_pYesMii->setPosition(origin.x + visibleSize.width / 2.0f - 100.0f, origin.y + visibleSize.height / 2.0f - 50);

	m_pNoMii = MenuItemImage::create("image/gamescene/no_btn_up.png", "image/gamescene/no_btn_down.png",
		CC_CALLBACK_1(GameScene0::menuNoCallback, this));
	m_pNoMii->setPosition(origin.x + visibleSize.width / 2.0f + 100.0f, origin.y + visibleSize.height / 2.0f - 50);

	m_pExitMenu = Menu::create(m_pYesMii, m_pNoMii, NULL);
	m_pExitMenu->setPosition(Vec2::ZERO);
	addChild(m_pExitMenu, 16);
	m_pExitMenu->setVisible(false);


	//创建蒙版
	m_pMaskImage = Sprite::create("image/gamescene/maskimage.png");
	m_pMaskImage->setScale(150);
	m_pMaskImage->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
	addChild(m_pMaskImage, 10);
	m_pMaskImage->setVisible(false);

	//菜单整合，关闭按钮  技能   商店   属性
	m_pMenu = Menu::create(pShopWin, pExitWin, pAttriWin,NULL);
	m_pMenu->setPosition(Vec2::ZERO);
	addChild(m_pMenu, 0);

	////小地图
	////小地图背景
	//Sprite *pSmallMap = Sprite::create("photo/smallMap.png");
	//pSmallMap->setPosition(900, 390);
	//addChild(pSmallMap, 1);


	//////////////技能面板
	//通用技能
	pAttackMii = MenuItemImage::create("photo/attack.png", "photo/attack-1.png",
		CC_CALLBACK_1(GameScene0::attack, this));
	pAttackMii->setPosition(40, 90);

	pRecoverMii = MenuItemImage::create("photo/recover.png", "photo/recover1.png", "photo/recover1.png",
		CC_CALLBACK_1(GameScene0::recover, this));
	pRecoverMii->setPosition(145, 25);

	pCureMii = MenuItemImage::create("photo/cure.png", "photo/cure1.png", "photo/cure1.png",
		CC_CALLBACK_1(GameScene0::cure, this));
	pCureMii->setPosition(195, 25);

	//人物技能
	if (myChoice == 1)
	{
		pSkill1Mii = MenuItemImage::create("photo/Houyi/Houyi1.png", "photo/Houyi/Houyi1-2.png", "photo/Houyi/Houyi1-2.png",
			CC_CALLBACK_1(GameScene0::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Houyi/Houyi2.png", "photo/Houyi/Houyi2-2.png", "photo/Houyi/Houyi2-2.png",
			CC_CALLBACK_1(GameScene0::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Houyi/Houyi3.png", "photo/Houyi/Houyi3-2.png", "photo/Houyi/Houyi3-2.png",
			CC_CALLBACK_1(GameScene0::Skill3, this));
	}
	else if (myChoice == 2)
	{
		pSkill1Mii = MenuItemImage::create("photo/Arthur/Arthur1.png", "photo/Arthur/Arthur1-2.png", "photo/Arthur/Arthur1-2.png",
			CC_CALLBACK_1(GameScene0::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Arthur/Arthur2.png", "photo/Arthur/Arthur2-2.png", "photo/Arthur/Arthur2-2.png",
			CC_CALLBACK_1(GameScene0::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Arthur/Arthur3.png", "photo/Arthur/Arthur3-2.png", "photo/Arthur/Arthur3-2.png",
			CC_CALLBACK_1(GameScene0::Skill3, this));
	}
	else
	{
		pSkill1Mii = MenuItemImage::create("photo/Daji/Daji1.png", "photo/Daji/Daji1-2.png", "photo/Daji/Daji1-2.png",
			CC_CALLBACK_1(GameScene0::Skill1, this));
		pSkill2Mii = MenuItemImage::create("photo/Daji/Daji2.png", "photo/Daji/Daji2-2.png", "photo/Daji/Daji2-2.png",
			CC_CALLBACK_1(GameScene0::Skill2, this));
		pSkill3Mii = MenuItemImage::create("photo/Daji/Daji3.png", "photo/Daji/Daji3-2.png", "photo/Daji/Daji3-2.png",
			CC_CALLBACK_1(GameScene0::Skill3, this));
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

void GameScene0::update(float delta)
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

	sprintf(m_Textbuffer, "%d", time_sec);
	m_pTime_secText->setString(m_Textbuffer);

	sprintf(m_Textbuffer, "%d", time_min);
	m_pTime_minText->setString(m_Textbuffer);

	//金钱更新
	if (m_pGameScene2->Hero.Money() != m_money)
	{
		m_money = m_pGameScene2->Hero.Money();
		sprintf(m_Textbuffer, "%d", m_money);
		m_pMoneyText->setString(m_Textbuffer);
	}


	/////技能冷却更新      8   12   18   10   15
	if (!m_Skill1Up)
	{
		m_pSkill1Text->setVisible(true);
		m_pass1 += delta;
		m_Skill1Wait = 8 - (int(m_pass1) % 60);
		sprintf(m_Textbuffer, "%d", m_Skill1Wait);
		m_pSkill1Text->setString(m_Textbuffer);
	}
	if (m_Skill1Wait <= 0)
	{
		m_pass1 = 0;
		m_Skill1Up = true;
		pSkill1Mii->setEnabled(true);
		sprintf(m_Textbuffer, "%d", m_Skill1Wait);
		m_pSkill1Text->setString(m_Textbuffer);
		m_pSkill1Text->setVisible(false);
	}

	if (!m_Skill2Up)
	{
		m_pSkill2Text->setVisible(true);
		m_pass2 += delta;
		m_Skill2Wait = 12 - (int(m_pass2) % 60);
		sprintf(m_Textbuffer, "%d", m_Skill2Wait);
		m_pSkill2Text->setString(m_Textbuffer);
	}
	if (m_Skill2Wait <= 0)
	{
		m_pass2 = 0;
		m_Skill2Up = true;
		pSkill2Mii->setEnabled(true);
		sprintf(m_Textbuffer, "%d", m_Skill2Wait);
		m_pSkill2Text->setString(m_Textbuffer);
		m_pSkill2Text->setVisible(false);
	}

	if (!m_Skill3Up)
	{
		m_pSkill3Text->setVisible(true);
		m_pass3 += delta;
		m_Skill3Wait = 18 - (int(m_pass3) % 60);
		sprintf(m_Textbuffer, "%d", m_Skill3Wait);
		m_pSkill3Text->setString(m_Textbuffer);
	}
	if (m_Skill3Wait <= 0)
	{
		m_pass3 = 0;
		m_Skill3Up = true;
		pSkill3Mii->setEnabled(true);
		sprintf(m_Textbuffer, "%d", m_Skill3Wait);
		m_pSkill3Text->setString(m_Textbuffer);
		m_pSkill3Text->setVisible(false);
	}

	if (!m_Skill4Up)
	{
		m_pSkill4Text->setVisible(true);
		m_pass4 += delta;
		m_Skill4Wait = 10 - (int(m_pass4) % 60);
		sprintf(m_Textbuffer, "%d", m_Skill4Wait);
		m_pSkill4Text->setString(m_Textbuffer);
	}
	if (m_Skill4Wait <= 0)
	{
		m_pass4 = 0;
		m_Skill4Up = true;
		pRecoverMii->setEnabled(true);
		sprintf(m_Textbuffer, "%d", m_Skill4Wait);
		m_pSkill4Text->setString(m_Textbuffer);
		m_pSkill4Text->setVisible(false);
	}

	if (!m_Skill5Up)
	{
		m_pSkill5Text->setVisible(true);
		m_pass5 += delta;
		m_Skill5Wait = 15 - (int(m_pass5) % 60);
		sprintf(m_Textbuffer, "%d", m_Skill5Wait);
		m_pSkill5Text->setString(m_Textbuffer);
	}
	if (m_Skill5Wait <= 0)
	{
		m_pass5 = 0;
		m_Skill5Up = true;
		pCureMii->setEnabled(true);
		sprintf(m_Textbuffer, "%d", m_Skill5Wait);
		m_pSkill5Text->setString(m_Textbuffer);
		m_pSkill5Text->setVisible(false);
	}

	
	///////////////////////属性更新

	if (m_kill != m_pGameScene2->Hero.m_kill)
	{
		m_kill = m_pGameScene2->Hero.m_kill;
		sprintf(m_Textbuffer, "%d", m_kill);
		m_pKillText->setString(m_Textbuffer);

		m_pKill2Text->setString(m_Textbuffer);
	}

	if (m_death != m_pGameScene2->Hero.m_death)
	{
		m_death = m_pGameScene2->Hero.m_death;
		sprintf(m_Textbuffer, "%d", m_death);
		m_pDeathText->setString(m_Textbuffer);
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

void GameScene0::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)    //////键盘事件
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


void GameScene0::openAttri(cocos2d::Ref * pSender)
{
	/*m_money2 = m_money;
	sprintf(m_Textbuffer, "%d", m_money2);
	m_pMoney2Text->setString(m_Textbuffer);
	m_pMoney2Text->setVisible(true);*/

	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_AttriBack1->setVisible(true);
	m_pAttriMenu->setVisible(true);
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
}

void GameScene0::transToOp(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
	m_AttriBack1->setVisible(true);
	m_AttriBack2->setVisible(false);
}

void GameScene0::transToHero(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(true);
	m_pHeroAttriMii->setEnabled(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(true);
}

void GameScene0::closeAttri(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(false);
	m_pAttriMenu->setVisible(false);
}

void GameScene0::openAttri2(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_AttriB1->setVisible(true);
	m_AttriMenu->setVisible(true);
	m_button1->setEnabled(false);
	m_button2->setEnabled(true);
}

void GameScene0::transTo1(cocos2d::Ref * pSender)
{
	m_button1->setEnabled(false);
	m_button2->setEnabled(true);
	m_AttriB1->setVisible(true);
	m_AttriB2->setVisible(false);
}

void GameScene0::transTo2(cocos2d::Ref * pSender)
{
	m_button1->setEnabled(true);
	m_button2->setEnabled(false);
	m_AttriB1->setVisible(false);
	m_AttriB2->setVisible(true);
}

void GameScene0::closeAttri2(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_AttriB1->setVisible(false);
	m_AttriB2->setVisible(false);
	m_AttriMenu->setVisible(false);
}

void GameScene0::openShop(cocos2d::Ref * pSender)
{
	m_money2 = m_money;
	sprintf(m_Textbuffer, "%d", m_money2);
	m_pMoney2Text->setString(m_Textbuffer);
	m_pMoney2Text->setVisible(true);

	m_pRecomBac->setVisible(true);
	m_pDownBac = m_pRecomBac;
	m_pRecommandMenu->setVisible(true);
	m_pDownMenu = m_pRecommandMenu;
	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_ShopBack->setVisible(true);
	m_pShopMenu->setVisible(true);
}

void GameScene0::closeShop(cocos2d::Ref * pSender)
{
	m_pMoney2Text->setVisible(false);

	m_pDownBac->setVisible(false);
	m_pDownMenu->setVisible(false);
	m_pMenu->setEnabled(true);
	m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_ShopBack->setVisible(false);
	m_pShopMenu->setVisible(false);
}

void GameScene0::openExit(cocos2d::Ref * pSender)
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

void GameScene0::menuYesCallback(cocos2d::Ref * pSender)
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



void GameScene0::menuNoCallback(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_ExitBack->setVisible(false);
	m_pExitMenu->setVisible(false);
	m_pMaskImage->setVisible(false);

}

void GameScene0::RecommendMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pRecomBac->setVisible(true);
	m_pDownBac = m_pRecomBac;

	m_pDownMenu->setVisible(false);
	m_pRecommandMenu->setVisible(true);
	m_pDownMenu = m_pRecommandMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::AttackMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pAttackBac->setVisible(true);
	m_pDownBac = m_pAttackBac;

	m_pDownMenu->setVisible(false);
	m_pAttackMenu->setVisible(true);
	m_pDownMenu = m_pAttackMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAttackMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::MagicMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pMagicBac->setVisible(true);
	m_pDownBac = m_pMagicBac;

	m_pDownMenu->setVisible(false);
	m_pMagicMenu->setVisible(true);
	m_pDownMenu = m_pMagicMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMagicMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::DefenseMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pDefenseBac->setVisible(true);
	m_pDownBac = m_pDefenseBac;

	m_pDownMenu->setVisible(false);
	m_pDefenseMenu->setVisible(true);
	m_pDownMenu = m_pDefenseMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pDefenseMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::MoveMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pMoveBac->setVisible(true);
	m_pDownBac = m_pMoveBac;

	m_pDownMenu->setVisible(false);
	m_pMoveMenu->setVisible(true);
	m_pDownMenu = m_pMoveMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMoveMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::BattleMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pBattleBac->setVisible(true);
	m_pDownBac = m_pBattleBac;

	m_pDownMenu->setVisible(false);
	m_pBattleMenu->setVisible(true);
	m_pDownMenu = m_pBattleMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pBattleMii;
	m_pDownMii->setEnabled(false);
}

void GameScene0::AssistMenu(cocos2d::Ref * pSender)
{
	m_pDownBac->setVisible(false);
	m_pAssistBac->setVisible(true);
	m_pDownBac = m_pAssistBac;

	m_pDownMenu->setVisible(false);
	m_pAssistMenu->setVisible(true);
	m_pDownMenu = m_pAssistMenu;
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAssistMii;
	m_pDownMii->setEnabled(false);
}
void GameScene0::attack0(cocos2d::Ref * pSender)
{
}
///////////////物品函数
void GameScene0::attack1(cocos2d::Ref * pSender)
{
}

void GameScene0::attack2(cocos2d::Ref * pSender)
{
}

void GameScene0::attack3(cocos2d::Ref * pSender)
{
}

void GameScene0::attack4(cocos2d::Ref * pSender)
{
}

void GameScene0::attack5(cocos2d::Ref * pSender)
{
}

void GameScene0::attack6(cocos2d::Ref * pSender)
{
}

void GameScene0::attack7(cocos2d::Ref * pSender)
{
}

void GameScene0::attack8(cocos2d::Ref * pSender)
{
}

void GameScene0::attack9(cocos2d::Ref * pSender)
{
}

void GameScene0::attack10(cocos2d::Ref * pSender)
{
}

void GameScene0::attack11(cocos2d::Ref * pSender)
{
}

void GameScene0::attack12(cocos2d::Ref * pSender)
{
}

void GameScene0::attack13(cocos2d::Ref * pSender)
{
}

void GameScene0::attack14(cocos2d::Ref * pSender)
{
}

void GameScene0::attack15(cocos2d::Ref * pSender)
{
}

void GameScene0::magic0(cocos2d::Ref * pSender)
{
}

void GameScene0::magic1(cocos2d::Ref * pSender)
{
}

void GameScene0::magic2(cocos2d::Ref * pSender)
{
}

void GameScene0::magic3(cocos2d::Ref * pSender)
{
}

void GameScene0::magic4(cocos2d::Ref * pSender)
{
}

void GameScene0::magic5(cocos2d::Ref * pSender)
{
}

void GameScene0::magic6(cocos2d::Ref * pSender)
{
}

void GameScene0::magic7(cocos2d::Ref * pSender)
{
}

void GameScene0::magic8(cocos2d::Ref * pSender)
{
}

void GameScene0::magic9(cocos2d::Ref * pSender)
{
}

void GameScene0::magic10(cocos2d::Ref * pSender)
{
}

void GameScene0::magic11(cocos2d::Ref * pSender)
{
}

void GameScene0::magic12(cocos2d::Ref * pSender)
{
}

void GameScene0::magic13(cocos2d::Ref * pSender)
{
}

void GameScene0::magic14(cocos2d::Ref * pSender)
{
}

void GameScene0::magic15(cocos2d::Ref * pSender)
{
}

void GameScene0::defense0(cocos2d::Ref * pSender)
{
}

void GameScene0::defense1(cocos2d::Ref * pSender)
{
}

void GameScene0::defense2(cocos2d::Ref * pSender)
{
}

void GameScene0::defense3(cocos2d::Ref * pSender)
{
}

void GameScene0::defense4(cocos2d::Ref * pSender)
{
}

void GameScene0::defense5(cocos2d::Ref * pSender)
{
}

void GameScene0::defense6(cocos2d::Ref * pSender)
{
}

void GameScene0::defense7(cocos2d::Ref * pSender)
{
}

void GameScene0::defense8(cocos2d::Ref * pSender)
{
}

void GameScene0::defense9(cocos2d::Ref * pSender)
{
}

void GameScene0::defense10(cocos2d::Ref * pSender)
{
}

void GameScene0::defense11(cocos2d::Ref * pSender)
{
}

void GameScene0::defense12(cocos2d::Ref * pSender)
{
}

void GameScene0::defense13(cocos2d::Ref * pSender)
{
}

void GameScene0::defense14(cocos2d::Ref * pSender)
{
}

void GameScene0::defense15(cocos2d::Ref * pSender)
{
}


void GameScene0::move0(cocos2d::Ref * pSender)
{
}

void GameScene0::move1(cocos2d::Ref * pSender)
{
}

void GameScene0::move2(cocos2d::Ref * pSender)
{
}

void GameScene0::move3(cocos2d::Ref * pSender)
{
}

void GameScene0::move4(cocos2d::Ref * pSender)
{
}

void GameScene0::move5(cocos2d::Ref * pSender)
{
}

void GameScene0::move6(cocos2d::Ref * pSender)
{
}


void GameScene0::battle0(cocos2d::Ref * pSender)
{
}

void GameScene0::battle1(cocos2d::Ref * pSender)
{
}

void GameScene0::battle2(cocos2d::Ref * pSender)
{
}

void GameScene0::battle3(cocos2d::Ref * pSender)
{
}

void GameScene0::battle4(cocos2d::Ref * pSender)
{
}

void GameScene0::battle5(cocos2d::Ref * pSender)
{
}

void GameScene0::battle6(cocos2d::Ref * pSender)
{
}



void GameScene0::assist0(cocos2d::Ref * pSender)
{
}

void GameScene0::assist1(cocos2d::Ref * pSender)
{
}

void GameScene0::assist2(cocos2d::Ref * pSender)
{
}

void GameScene0::assist3(cocos2d::Ref * pSender)
{
}

void GameScene0::assist4(cocos2d::Ref * pSender)
{
}

void GameScene0::assist5(cocos2d::Ref * pSender)
{
}

void GameScene0::assist6(cocos2d::Ref * pSender)
{
}

void GameScene0::assist7(cocos2d::Ref * pSender)
{
}

void GameScene0::assist8(cocos2d::Ref * pSender)
{
}







void GameScene0::attack(cocos2d::Ref* pSender)
{
	//pAttackMii->setEnabled(false);
}

void GameScene0::recover(cocos2d::Ref* pSender)
{
	m_Skill4Up = false;
	pRecoverMii->setEnabled(false);
}

void GameScene0::cure(cocos2d::Ref* pSender)
{
	m_Skill5Up = false;
	pCureMii->setEnabled(false);
}

void GameScene0::Skill1(cocos2d::Ref* pSender)
{
	m_Skill1Up = false;
	pSkill1Mii->setEnabled(false);

}

void GameScene0::Skill2(cocos2d::Ref* pSender)
{
	m_Skill2Up = false;
	pSkill2Mii->setEnabled(false);
}

void GameScene0::Skill3(cocos2d::Ref* pSender)
{
	m_Skill3Up = false;
	pSkill3Mii->setEnabled(false);
}









