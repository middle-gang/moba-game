#include "GameScene0.h"
#include"MainMenu.h"

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


	///技能冷却时间
	SkillWait[0] = 6;
	SkillWait[1] = 6;
	SkillWait[2] = 15;
	SkillWait[3] = 10;
	SkillWait[4] = 15;

	m_SkillWait[0] = 6;
	m_SkillWait[1] = 6;
	m_SkillWait[2] = 15;
	m_SkillWait[3] = 10;
	m_SkillWait[4] = 15;

	for (int i = 0; i < 5; i++) {
		m_pass[i] = 0;
		m_SkillUp[i] = true;
	}

	sprintf(m_Textbuffer, "%d", m_SkillWait[0]);
	m_pSkillText[0] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkillText[0]->setPosition(80, 145);

	sprintf(m_Textbuffer, "%d", m_SkillWait[1]);
	m_pSkillText[1] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkillText[1]->setPosition(130, 85);

	sprintf(m_Textbuffer, "%d", m_SkillWait[2]);
	m_pSkillText[2] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkillText[2]->setPosition(80, 25);

	sprintf(m_Textbuffer, "%d", m_SkillWait[3]);
	m_pSkillText[3] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkillText[3]->setPosition(150, 20);

	sprintf(m_Textbuffer, "%d", m_SkillWait[4]);
	m_pSkillText[4] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pSkillText[4]->setPosition(200, 20);

	for (int i = 0; i < 5; i++) {
		addChild(m_pSkillText[i],3);
		m_pSkillText[i]->setVisible(false);
	}

	//////////////技能面板
	//通用技能
	pSkillMii[3] = Sprite::create("photo/recover.png");
	pSkillMii[3]->setPosition(145, 25);
	pSkillMii1[3] = Sprite::create("photo/recover1.png");
	pSkillMii1[3]->setPosition(145, 25);

	pSkillMii[4] = Sprite::create("photo/cure.png");
	pSkillMii[4]->setPosition(195, 25);
	pSkillMii1[4] = Sprite::create("photo/cure1.png");
	pSkillMii1[4]->setPosition(195, 25);
	//人物技能
	if (myChoice == 1) {
		pSkillMii[0] = Sprite::create("photo/Houyi/Houyi1.png");
		pSkillMii1[0] = Sprite::create("photo/Houyi/Houyi1-2.png");
		pSkillMii[1] = Sprite::create("photo/Houyi/Houyi2.png");
		pSkillMii1[1] = Sprite::create("photo/Houyi/Houyi2-2.png");
		pSkillMii[2] = Sprite::create("photo/Houyi/Houyi3.png");
		pSkillMii1[2] = Sprite::create("photo/Houyi/Houyi3-2.png");
	}
	else if (myChoice == 2) {
		pSkillMii[0] = Sprite::create("photo/Arthur/Arthur1.png");
		pSkillMii1[0] = Sprite::create("photo/Arthur/Arthur1-2.png");
		pSkillMii[1] = Sprite::create("photo/Arthur/Arthur2.png");
		pSkillMii1[1] = Sprite::create("photo/Arthur/Arthur2-2.png");
		pSkillMii[2] = Sprite::create("photo/Arthur/Arthur3.png");
		pSkillMii1[2] = Sprite::create("photo/Arthur/Arthur3-2.png");
	}
	else {
		pSkillMii[0] = Sprite::create("photo/Daji/Daji1.png");
		pSkillMii1[0] = Sprite::create("photo/Daji/Daji1-2.png");
		pSkillMii[1] = Sprite::create("photo/Daji/Daji2.png");
		pSkillMii1[1] = Sprite::create("photo/Daji/Daji2-2.png");
		pSkillMii[2] = Sprite::create("photo/Daji/Daji3.png");
		pSkillMii1[2] = Sprite::create("photo/Daji/Daji3-2.png");
	}
	pSkillMii[0]->setPosition(70, 150);
	pSkillMii[1]->setPosition(120, 90);
	pSkillMii[2]->setPosition(70, 30);
	pSkillMii1[0]->setPosition(70, 150);
	pSkillMii1[1]->setPosition(120, 90);
	pSkillMii1[2]->setPosition(70, 30);
	for (int i = 0; i < 5; i++)
	{
		pSkillMii[i]->setVisible(true);
		pSkillMii1[i]->setVisible(false);
		addChild(pSkillMii[i], 1);
		addChild(pSkillMii1[i], 2);
	}

	//////////卖）装备相关数据初始化      小地图位置初始化
	memset(&n1, 0, sizeof(n1));
	memset(&n2, 0, sizeof(n2));
	memset(&EquipNumber, 100, sizeof(EquipNumber));
	posX = m_pGameScene2->PosX()/10+855;
	posY =  340+m_pGameScene2->PosY()/10;
	////////////////////////////////英雄属性
	m_kill = m_pGameScene2->Hero.m_kill;
	e_kill = m_pGameScene2->Hero.E_Kill();
	m_death = m_pGameScene2->Hero.m_death;
	m_level = m_pGameScene2->Hero.Level();
	m_money = m_pGameScene2->Hero.Money();
	t_money = m_pGameScene2->Hero.tMoney();

	m_attack = m_pGameScene2->Hero.AttackPower();//攻击力
	m_power = m_pGameScene2->Hero.Power();//法术强度
	m_health = m_pGameScene2->Hero.totalHealth();//总生命值
	magicpoint = m_pGameScene2->Hero.MagicPoint();//法力值
	armor = m_pGameScene2->Hero.Armor();//护甲值
	magicDenfence = m_pGameScene2->Hero.MagicDefence();//魔抗
	attackingSpeed = m_pGameScene2->Hero.AttackSpeed();  //攻击速度
	waitLessen = m_pGameScene2->Hero.WaitLessen();//冷却缩减
	velocity = m_pGameScene2->Hero.getVelocity();//移动速度
	healthRecover = m_pGameScene2->Hero.HealthRecover();//生命回复
	magicpointRecover = m_pGameScene2->Hero.MagicPointRecover();//法力回复 
	armorIgnore = m_pGameScene2->Hero.ArmorIgnore();//护甲穿透
	magicdenfenceIgnore = m_pGameScene2->Hero.MagicDefenseIgnore();//法术穿透
	physicBloodSuck = m_pGameScene2->Hero.PhysicBloodSuck();//物理吸血
	magicBloodSuck = m_pGameScene2->Hero.MagicBloodSuck();//法术吸血

	//bool buy = false;
	 ///////////////////属性数值显示

	sprintf(m_Textbuffer, "%d", m_kill);
	m_pKillText[0] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKillText[0]->setPosition(100, 435);
	addChild(m_pKillText[0], 3);

	m_pKillText[1] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKillText[1]->setColor(Color3B::BLUE);
	m_pKillText[1]->setPosition(165, 405);
	addChild(m_pKillText[1], 3);

	m_pKillText[2] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 22);
	m_pKillText[2]->setPosition(342, 287);
	addChild(m_pKillText[2], 13);
	m_pKillText[2]->setVisible(false);

	sprintf(m_Textbuffer, "%d", e_kill);
	e_pKillText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	e_pKillText->setColor(Color3B::RED);
	e_pKillText->setPosition(220, 405);
	addChild(e_pKillText, 3);

	sprintf(m_Textbuffer, "%d", m_death);
	m_pDeathText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);//窗口
	m_pDeathText->setPosition(150, 435);
	addChild(m_pDeathText, 3);

	m_pDeath2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 22);
	m_pDeath2Text->setPosition(390, 287);
	addChild(m_pDeath2Text, 13);
	m_pDeath2Text->setVisible(false);

	Label* m_pAssist = Label::createWithTTF("0", "fonts/msyh.ttc", 23);
	m_pAssist->setPosition(200, 435);
	addChild(m_pAssist, 3);

	//生命值
	sprintf(m_Textbuffer, "%d", m_health);
	m_pAttri1Text[0] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pAttri1Text[0]->setPosition(220,250);
	addChild(m_pAttri1Text[0], 13);

	m_pAttri2Text[2] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[2], 13);

	//物理攻击
	sprintf(m_Textbuffer, "%0.0f", m_attack);
	m_pAttri1Text[1] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pAttri1Text[1]->setPosition(280, 250);
	addChild(m_pAttri1Text[1], 13);

	m_pAttri2Text[0] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[0], 13);
	//法术攻击
	sprintf(m_Textbuffer, "%0.0f", m_power);
	m_pAttri1Text[2] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pAttri1Text[2]->setPosition(330,250);
	addChild(m_pAttri1Text[2], 13);

	m_pAttri2Text[1] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[1], 13);
	//物理防御
	sprintf(m_Textbuffer, "%0.0f", armor);
	m_pAttri1Text[3] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pAttri1Text[3]->setPosition(382, 250);
	addChild(m_pAttri1Text[3], 13);
	
	m_pAttri2Text[4] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[4], 13);

	//法术防御
	sprintf(m_Textbuffer, "%0.0f", magicDenfence);
	m_pAttri1Text[4] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	m_pAttri1Text[4]->setPosition(434, 250);
	addChild(m_pAttri1Text[4], 13);
	
	m_pAttri2Text[5] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[5], 13);

	//最大法力值
	sprintf(m_Textbuffer, "%d", magicpoint);
	m_pAttri2Text[3] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[3], 13);
	//攻击速度
	sprintf(m_Textbuffer, "%0.1f", attackingSpeed);
	m_pAttri2Text[6] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[6], 13);
	//冷却缩减
	sprintf(m_Textbuffer, "%0.0f", waitLessen);
	m_pAttri2Text[7] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[7], 13);
	//暴击概率
	m_pAttri2Text[8] = Label::createWithTTF("0", "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[8], 13);
	//移动速度
	sprintf(m_Textbuffer, "%0.0f", velocity);
	m_pAttri2Text[9] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[9], 13);
	//回血
	sprintf(m_Textbuffer, "%d", healthRecover);
	m_pAttri2Text[10] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[10], 13);
	//回蓝
	sprintf(m_Textbuffer, "%d", magicpointRecover);
	m_pAttri2Text[11] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[11], 13);
	//物理穿透
	sprintf(m_Textbuffer, "%0.0f", armorIgnore);
	m_pAttri2Text[12] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[12], 13);
	//法术穿透
	sprintf(m_Textbuffer, "%0.0f", magicdenfenceIgnore);
	m_pAttri2Text[13] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[13], 13);
	//物理吸血
	sprintf(m_Textbuffer, "%0.0f", physicBloodSuck);
	m_pAttri2Text[14] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[14], 13);
	//法术吸血
	sprintf(m_Textbuffer, "%0.0f", magicBloodSuck);
	m_pAttri2Text[15] = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 20);
	addChild(m_pAttri2Text[15], 13);

	for (int i = 0; i < 5; i++){
		m_pAttri1Text[i]->setVisible(false);
	}
	for (int i = 0; i < 16; i++){
		if (i % 2 == 0)
			m_pAttri2Text[i]->setPosition(460, 283 - 26 * (i / 2));
		else
			m_pAttri2Text[i]->setPosition(740, 283 - 26 * (i / 2));
		m_pAttri2Text[i]->setVisible(false);
	}
	//////金钱显示
	sprintf(m_Textbuffer, "%d", m_money);
	m_pMoneyText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 15);
	m_pMoneyText->setColor(Color3B::BLACK);
	m_pMoneyText->setPosition(928, 189);
	addChild(m_pMoneyText, 3);

	m_pMoney2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pMoney2Text->setColor(Color3B::BLUE);
	m_pMoney2Text->setPosition(180, 375);
	m_pMoney2Text->setVisible(false);
	addChild(m_pMoney2Text, 13);

	t_pMoneyText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 22);
	t_pMoneyText->setPosition(436, 325);
	t_pMoneyText->setVisible(false);
	addChild(t_pMoneyText, 13);

	t_pMoney2Text = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 22);
	t_pMoney2Text->setPosition(493, 288);
	t_pMoney2Text->setVisible(false);
	addChild(t_pMoney2Text, 13);



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

	////////////////////////////////////////////////////////创建属性1111111界面
	AttriIsOpen = false;
	Sprite *m_pAttriWin = Sprite::create("photo/main/box1.png");
	m_pAttriWin->setPosition(160, 420);
	addChild(m_pAttriWin, 1);

	m_AttriBack1 = Sprite::create("photo/Attribute/dialogue1.png");
	m_AttriBack1->setPosition(500, 236.5);
	addChild(m_AttriBack1, 11);
	m_AttriBack1->setVisible(false);

	m_AttriBack2 = Sprite::create("photo/Attribute/dialogue2.png");
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
	
	//按钮：英雄属性
	m_button1 = MenuItemImage::create("photo/Attribute/button1.png",
		"photo/Attribute/button1-1.png",
		"photo/Attribute/button1-1.png",
		CC_CALLBACK_1(GameScene0::transTo1, this));
	m_button1->setPosition(166, 328);
	m_button1->setEnabled(false);
	//按钮：装备
	m_button2 = MenuItemImage::create("photo/Attribute/button2.png",
		"photo/Attribute/button2-1.png",
		"photo/Attribute/button2-1.png",
		CC_CALLBACK_1(GameScene0::transTo2, this));
	m_button2->setPosition(166, 286);

	m_closebutton = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(GameScene0::closeAttri2, this));
	m_closebutton->setPosition(870, 400);

	m_AttriMenu = Menu::create(m_button1, m_button2, m_closebutton, NULL);
	m_AttriMenu->setPosition(Vec2::ZERO);
	addChild(m_AttriMenu, 12);
	m_AttriMenu->setVisible(false);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////出售
	SaleMII[0] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip0, this));
	SaleMII[1] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip1, this));
	SaleMII[2] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip2, this));
	SaleMII[3] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip3, this));
	SaleMII[4] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip4, this));
	SaleMII[5] = MenuItemImage::create("photo/shop/sale.png",
		"photo/shop/sale1.png",
		CC_CALLBACK_1(GameScene0::sellEquip5, this));
	
	for (int i = 0; i < 6; i++) {
		SaleMII[i]->setPosition(300 + 100 * i, 200);
		SaleMII[i]->setVisible(false);
	}
	pSaleMenu = Menu::create(SaleMII[0], SaleMII[1], SaleMII[2], SaleMII[3], SaleMII[4], SaleMII[5],NULL);
	pSaleMenu->setPosition(Vec2::ZERO);
	addChild(pSaleMenu, 21);
	

	/////////////////////////////创建商店界面
	ShopIsOpen = false;
	MenuItemImage * pShopWin = MenuItemImage::create("photo/shop.png", "photo/shop1.png",
		CC_CALLBACK_1(GameScene0::openShop, this));
	pShopWin->setPosition(930, 200);


	//商店背景
	m_ShopBack = Sprite::create("photo/shop/background.png");
	m_ShopBack->setPosition(500, 236.5);
	addChild(m_ShopBack, 11);
	m_ShopBack->setVisible(false);

	/////////////////////////////////////////////////////////////////////////////////商店物品

	//////////////////////////////////////////////////////按钮
	////推荐
	m_pBac[0] = Sprite::create("photo/shop/recomB.png");
	addChild(m_pBac[0], 14);
	//推荐界面
	 Equip[0][0] = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(GameScene0::move0, this));
	 Equip[0][1] = MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(GameScene0::defense0, this));
	 Equip[0][2] = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(GameScene0::defense1, this));
	 Equip[0][3] = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(GameScene0::defense2, this));
	 Equip[0][4] = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(GameScene0::magic1, this));

	for (int i = 0; i <= 3; i++){
		 Equip[0][i]->setPosition(270 + i * 120, 370);
		// Equip[0][i]->setEnabled(false);
	}
	 Equip[0][4]->setPosition(270, 285);
	// Equip[0][4]->setEnabled(false);

	m_pShopMenu[0] = Menu::create( Equip[0][0],  Equip[0][1],  Equip[0][2],  Equip[0][3],
		 Equip[0][4], NULL);

	/////攻击
	m_pBac[1] = Sprite::create("photo/shop/attackB.png");
	addChild(m_pBac[1], 14);
	//攻击界面
	 Equip[1][0] = MenuItemImage::create("photo/shop/attack/1.jpg",
		"photo/shop/attack/1_1.jpg",
		"photo/shop/attack/1_1.jpg",
		CC_CALLBACK_1(GameScene0::attack0, this));
	 Equip[1][1] = MenuItemImage::create("photo/shop/attack/2.jpg",
		"photo/shop/attack/2_1.jpg",
		"photo/shop/attack/2_1.jpg",
		CC_CALLBACK_1(GameScene0::attack1, this));
	 Equip[1][2] = MenuItemImage::create("photo/shop/attack/3.jpg",
		"photo/shop/attack/3_1.jpg",
		"photo/shop/attack/3_1.jpg",
		CC_CALLBACK_1(GameScene0::attack2, this));
	 Equip[1][3] = MenuItemImage::create("photo/shop/attack/4.jpg",
		"photo/shop/attack/4_1.jpg",
		"photo/shop/attack/4_1.jpg",
		CC_CALLBACK_1(GameScene0::attack3, this));
	 Equip[1][4] = MenuItemImage::create("photo/shop/attack/5.jpg",
		"photo/shop/attack/5_1.jpg",
		"photo/shop/attack/5_1.jpg",
		CC_CALLBACK_1(GameScene0::attack4, this));
	 Equip[1][5] = MenuItemImage::create("photo/shop/attack/6.jpg",
		"photo/shop/attack/6_1.jpg",
		"photo/shop/attack/6_1.jpg",
		CC_CALLBACK_1(GameScene0::attack5, this));
	 Equip[1][6] = MenuItemImage::create("photo/shop/attack/7.jpg",
		"photo/shop/attack/7_1.jpg",
		"photo/shop/attack/7_1.jpg",
		CC_CALLBACK_1(GameScene0::attack6, this));
	 Equip[1][7] = MenuItemImage::create("photo/shop/attack/8.jpg",
		"photo/shop/attack/8_1.jpg",
		"photo/shop/attack/8_1.jpg",
		CC_CALLBACK_1(GameScene0::attack7, this));
	 Equip[1][8] = MenuItemImage::create("photo/shop/attack/9.jpg",
		"photo/shop/attack/9_1.jpg",
		"photo/shop/attack/9_1.jpg",
		CC_CALLBACK_1(GameScene0::attack8, this));
	 Equip[1][9] = MenuItemImage::create("photo/shop/attack/10.jpg",
		"photo/shop/attack/10_1.jpg",
		"photo/shop/attack/10_1.jpg",
		CC_CALLBACK_1(GameScene0::attack9, this));
	 Equip[1][10] = MenuItemImage::create("photo/shop/attack/11.jpg",
		"photo/shop/attack/11_1.jpg",
		"photo/shop/attack/11_1.jpg",
		CC_CALLBACK_1(GameScene0::attack10, this));
	 Equip[1][11] = MenuItemImage::create("photo/shop/attack/12.jpg",
		"photo/shop/attack/12_1.jpg",
		"photo/shop/attack/12_1.jpg",
		CC_CALLBACK_1(GameScene0::attack11, this));
	 Equip[1][12] = MenuItemImage::create("photo/shop/attack/13.jpg",
		"photo/shop/attack/13_1.jpg",
		"photo/shop/attack/13_1.jpg",
		CC_CALLBACK_1(GameScene0::attack12, this));
	 Equip[1][13] = MenuItemImage::create("photo/shop/attack/14.jpg",
		"photo/shop/attack/14_1.jpg",
		"photo/shop/attack/14_1.jpg",
		CC_CALLBACK_1(GameScene0::attack13, this));
	 Equip[1][14] = MenuItemImage::create("photo/shop/attack/15.jpg",
		"photo/shop/attack/15_1.jpg",
		"photo/shop/attack/15_1.jpg",
		CC_CALLBACK_1(GameScene0::attack13, this));
	 Equip[1][15] = MenuItemImage::create("photo/shop/attack/16.jpg",
		"photo/shop/attack/16_1.jpg",
		"photo/shop/attack/16_1.jpg",
		CC_CALLBACK_1(GameScene0::attack14, this));

	//法术
	m_pBac[2] = Sprite::create("photo/shop/magicB.png");
	addChild(m_pBac[2], 14);
	//法术界面
	 Equip[2][0] = MenuItemImage::create("photo/shop/magic/1.jpg",
		"photo/shop/magic/1_1.jpg",
		"photo/shop/magic/1_1.jpg",
		CC_CALLBACK_1(GameScene0::magic0, this));
	 Equip[2][1] = MenuItemImage::create("photo/shop/magic/2.jpg",
		"photo/shop/magic/2_1.jpg",
		"photo/shop/magic/2_1.jpg",
		CC_CALLBACK_1(GameScene0::magic1, this));
	 Equip[2][2] = MenuItemImage::create("photo/shop/magic/3.jpg",
		"photo/shop/magic/3_1.jpg",
		"photo/shop/magic/3_1.jpg",
		CC_CALLBACK_1(GameScene0::magic2, this));
	 Equip[2][3] = MenuItemImage::create("photo/shop/magic/4.jpg",
		"photo/shop/magic/4_1.jpg",
		"photo/shop/magic/4_1.jpg",
		CC_CALLBACK_1(GameScene0::magic3, this));
	 Equip[2][4] = MenuItemImage::create("photo/shop/magic/5.jpg",
		"photo/shop/magic/5_1.jpg",
		"photo/shop/magic/5_1.jpg",
		CC_CALLBACK_1(GameScene0::magic4, this));
	 Equip[2][5] = MenuItemImage::create("photo/shop/magic/6.jpg",
		"photo/shop/magic/6_1.jpg",
		"photo/shop/magic/6_1.jpg",
		CC_CALLBACK_1(GameScene0::magic5, this));
	 Equip[2][6] = MenuItemImage::create("photo/shop/magic/7.jpg",
		"photo/shop/magic/7_1.jpg",
		"photo/shop/magic/7_1.jpg",
		CC_CALLBACK_1(GameScene0::magic6, this));
	 Equip[2][7] = MenuItemImage::create("photo/shop/magic/8.jpg",
		"photo/shop/magic/8_1.jpg",
		"photo/shop/magic/8_1.jpg",
		CC_CALLBACK_1(GameScene0::magic7, this));
	 Equip[2][8] = MenuItemImage::create("photo/shop/magic/9.jpg",
		"photo/shop/magic/9_1.jpg",
		"photo/shop/magic/9_1.jpg",
		CC_CALLBACK_1(GameScene0::magic8, this));
	 Equip[2][9] = MenuItemImage::create("photo/shop/magic/10.jpg",
		"photo/shop/magic/10_1.jpg",
		"photo/shop/magic/10_1.jpg",
		CC_CALLBACK_1(GameScene0::magic9, this));
	 Equip[2][10] = MenuItemImage::create("photo/shop/magic/11.jpg",
		"photo/shop/magic/11_1.jpg",
		"photo/shop/magic/11_1.jpg",
		CC_CALLBACK_1(GameScene0::magic10, this));
	 Equip[2][11] = MenuItemImage::create("photo/shop/magic/12.jpg",
		"photo/shop/magic/12_1.jpg",
		"photo/shop/magic/12_1.jpg",
		CC_CALLBACK_1(GameScene0::magic11, this));
	 Equip[2][12] = MenuItemImage::create("photo/shop/magic/13.jpg",
		"photo/shop/magic/13_1.jpg",
		"photo/shop/magic/13_1.jpg",
		CC_CALLBACK_1(GameScene0::magic12, this));
	 Equip[2][13] = MenuItemImage::create("photo/shop/magic/14.jpg",
		"photo/shop/magic/14_1.jpg",
		"photo/shop/magic/14_1.jpg",
		CC_CALLBACK_1(GameScene0::magic13, this));
	 Equip[2][14] = MenuItemImage::create("photo/shop/magic/15.jpg",
		"photo/shop/magic/15_1.jpg",
		"photo/shop/magic/15_1.jpg",
		CC_CALLBACK_1(GameScene0::magic14, this));
	 Equip[2][15] = MenuItemImage::create("photo/shop/magic/16.jpg",
		"photo/shop/magic/16_1.jpg",
		"photo/shop/magic/16_1.jpg",
		CC_CALLBACK_1(GameScene0::magic15, this));

	///防御
	m_pBac[3] = Sprite::create("photo/shop/defenseB.png");
	addChild(m_pBac[3], 14);
	//防御界面
	 Equip[3][0] = MenuItemImage::create("photo/shop/defense/1.jpg",
		"photo/shop/defense/1_1.jpg",
		"photo/shop/defense/1_1.jpg",
		CC_CALLBACK_1(GameScene0::defense0, this));
	 Equip[3][1] = MenuItemImage::create("photo/shop/defense/2.jpg",
		"photo/shop/defense/2_1.jpg",
		"photo/shop/defense/2_1.jpg",
		CC_CALLBACK_1(GameScene0::defense1, this));
	 Equip[3][2] = MenuItemImage::create("photo/shop/defense/3.jpg",
		"photo/shop/defense/3_1.jpg",
		"photo/shop/defense/3_1.jpg",
		CC_CALLBACK_1(GameScene0::defense2, this));
	 Equip[3][3] = MenuItemImage::create("photo/shop/defense/4.jpg",
		"photo/shop/defense/4_1.jpg",
		"photo/shop/defense/4_1.jpg",
		CC_CALLBACK_1(GameScene0::defense3, this));
	 Equip[3][4] = MenuItemImage::create("photo/shop/defense/5.jpg",
		"photo/shop/defense/5_1.jpg",
		"photo/shop/defense/5_1.jpg",
		CC_CALLBACK_1(GameScene0::defense4, this));
	 Equip[3][5] = MenuItemImage::create("photo/shop/defense/6.jpg",
		"photo/shop/defense/6_1.jpg",
		"photo/shop/defense/6_1.jpg",
		CC_CALLBACK_1(GameScene0::defense5, this));
	 Equip[3][6] = MenuItemImage::create("photo/shop/defense/7.jpg",
		"photo/shop/defense/7_1.jpg",
		"photo/shop/defense/7_1.jpg",
		CC_CALLBACK_1(GameScene0::defense6, this));
	 Equip[3][7] = MenuItemImage::create("photo/shop/defense/8.jpg",
		"photo/shop/defense/8_1.jpg",
		"photo/shop/defense/8_1.jpg",
		CC_CALLBACK_1(GameScene0::defense7, this));
	 Equip[3][8] = MenuItemImage::create("photo/shop/defense/9.jpg",
		"photo/shop/defense/9_1.jpg",
		"photo/shop/defense/9_1.jpg",
		CC_CALLBACK_1(GameScene0::defense8, this));
	 Equip[3][9] = MenuItemImage::create("photo/shop/defense/10.jpg",
		"photo/shop/defense/10_1.jpg",
		"photo/shop/defense/10_1.jpg",
		CC_CALLBACK_1(GameScene0::defense9, this));
	 Equip[3][10] = MenuItemImage::create("photo/shop/defense/11.jpg",
		"photo/shop/defense/11_1.jpg",
		"photo/shop/defense/11_1.jpg",
		CC_CALLBACK_1(GameScene0::defense10, this));
	 Equip[3][11] = MenuItemImage::create("photo/shop/defense/12.jpg",
		"photo/shop/defense/12_1.jpg",
		"photo/shop/defense/12_1.jpg",
		CC_CALLBACK_1(GameScene0::defense11, this));
	 Equip[3][12] = MenuItemImage::create("photo/shop/defense/13.jpg",
		"photo/shop/defense/13_1.jpg",
		"photo/shop/defense/13_1.jpg",
		CC_CALLBACK_1(GameScene0::defense12, this));
	 Equip[3][13] = MenuItemImage::create("photo/shop/defense/14.jpg",
		"photo/shop/defense/14_1.jpg",
		"photo/shop/defense/14_1.jpg",
		CC_CALLBACK_1(GameScene0::defense13, this));
	 Equip[3][14] = MenuItemImage::create("photo/shop/defense/15.jpg",
		"photo/shop/defense/15_1.jpg",
		"photo/shop/defense/15_1.jpg",
		CC_CALLBACK_1(GameScene0::defense14, this));
	 Equip[3][15] = MenuItemImage::create("photo/shop/defense/16.jpg",
		"photo/shop/defense/16_1.jpg",
		"photo/shop/defense/16_1.jpg",
		CC_CALLBACK_1(GameScene0::defense15, this));
	 ///攻击、法术、防御菜单
	 for(int j=1;j<4;j++){
		 for (int i = 0; i <= 15; i++) {
			// Equipbuy[j][i] = false;
			 if (i <= 3) {
				 Equip[j][i]->setPosition(270 + i * 120, 370);
			 }
			 else {
				 Equip[j][i]->setPosition(270 + (i % 4) * 120, 370 - (i / 4) * 85);
			 }
		 }

	m_pShopMenu[j] = Menu::create( Equip[j][0],  Equip[j][1],  Equip[j][2],  Equip[j][3],
		 Equip[j][4],  Equip[j][5],  Equip[j][6],  Equip[j][7],
		 Equip[j][8],  Equip[j][9],  Equip[j][10],  Equip[j][11],
		 Equip[j][12],  Equip[j][13],  Equip[j][14],  Equip[j][15], NULL);}

	///移动
	m_pBac[4] = Sprite::create("photo/shop/moveB.png");
	addChild(m_pBac[4], 14);
	//移动界面
	 Equip[4][0] = MenuItemImage::create("photo/shop/move/1.jpg",
		"photo/shop/move/1_1.jpg",
		"photo/shop/move/1_1.jpg",
		CC_CALLBACK_1(GameScene0::move0, this));
	 Equip[4][1] = MenuItemImage::create("photo/shop/move/2.jpg",
		"photo/shop/move/2_1.jpg",
		"photo/shop/move/2_1.jpg",
		CC_CALLBACK_1(GameScene0::move1, this));
	 Equip[4][2] = MenuItemImage::create("photo/shop/move/3.jpg",
		"photo/shop/move/3_1.jpg",
		"photo/shop/move/3_1.jpg",
		CC_CALLBACK_1(GameScene0::move2, this));
	 Equip[4][3] = MenuItemImage::create("photo/shop/move/4.jpg",
		"photo/shop/move/4_1.jpg",
		"photo/shop/move/4_1.jpg",
		CC_CALLBACK_1(GameScene0::move3, this));
	 Equip[4][4] = MenuItemImage::create("photo/shop/move/5.jpg",
		"photo/shop/move/5_1.jpg",
		"photo/shop/move/5_1.jpg",
		CC_CALLBACK_1(GameScene0::move4, this));
	 Equip[4][5] = MenuItemImage::create("photo/shop/move/6.jpg",
		"photo/shop/move/6_1.jpg",
		"photo/shop/move/6_1.jpg",
		CC_CALLBACK_1(GameScene0::move5, this));
	 Equip[4][6] = MenuItemImage::create("photo/shop/move/7.jpg",
		"photo/shop/move/7_1.jpg",
		"photo/shop/move/7_1.jpg",
		CC_CALLBACK_1(GameScene0::move6, this));
	
	///打野
	 m_pBac[5] = Sprite::create("photo/shop/battleB.png");
	 addChild(m_pBac[5], 14);
	//打野界面
	 Equip[5][0] = MenuItemImage::create("photo/shop/battle/1.jpg",
		"photo/shop/battle/1_1.jpg",
		"photo/shop/battle/1_1.jpg",
		CC_CALLBACK_1(GameScene0::battle0, this));
	 Equip[5][1] = MenuItemImage::create("photo/shop/battle/2.jpg",
		"photo/shop/battle/2_1.jpg",
		"photo/shop/battle/2_1.jpg",
		CC_CALLBACK_1(GameScene0::battle1, this));
	 Equip[5][2] = MenuItemImage::create("photo/shop/battle/3.jpg",
		"photo/shop/battle/3_1.jpg",
		"photo/shop/battle/3_1.jpg",
		CC_CALLBACK_1(GameScene0::battle2, this));
	 Equip[5][3] = MenuItemImage::create("photo/shop/battle/4.jpg",
		"photo/shop/battle/4_1.jpg",
		"photo/shop/battle/4_1.jpg",
		CC_CALLBACK_1(GameScene0::battle3, this));
	 Equip[5][4] = MenuItemImage::create("photo/shop/battle/5.jpg",
		"photo/shop/battle/5_1.jpg",
		"photo/shop/battle/5_1.jpg",
		CC_CALLBACK_1(GameScene0::battle4, this));
	 Equip[5][5] = MenuItemImage::create("photo/shop/battle/6.jpg",
		"photo/shop/battle/6_1.jpg",
		"photo/shop/battle/6_1.jpg",
		CC_CALLBACK_1(GameScene0::battle5, this));
	 Equip[5][6] = MenuItemImage::create("photo/shop/battle/7.jpg",
		"photo/shop/battle/7_1.jpg",
		"photo/shop/battle/7_1.jpg",
		CC_CALLBACK_1(GameScene0::battle6, this));

	 for (int j = 4; j <= 5; j++) {
		 for (int i = 0; i <= 6; i++) {
			// Equipbuy[j][i] = false;
			 if (i <= 3) {
				 Equip[j][i]->setPosition(270 + i * 120, 370);
			 }
			 else {
				 Equip[j][i]->setPosition(270 + (i % 4) * 120, 370 - (i / 4) * 85);
			 }
		 }
		 m_pShopMenu[j] = Menu::create(Equip[j][0], Equip[j][1], Equip[j][2], Equip[j][3],Equip[j][4], Equip[j][5], Equip[j][6], NULL);
	 }
	
	///辅助
	m_pBac[6] = Sprite::create("photo/shop/assistB.png");
	addChild(m_pBac[6], 14);
	//辅助界面
	 Equip[6][0] = MenuItemImage::create("photo/shop/assist/1.jpg",
		"photo/shop/assist/1_1.jpg",
		"photo/shop/assist/1_1.jpg",
		CC_CALLBACK_1(GameScene0::assist0, this));
	 Equip[6][1] = MenuItemImage::create("photo/shop/assist/2.jpg",
		"photo/shop/assist/2_1.jpg",
		"photo/shop/assist/2_1.jpg",
		CC_CALLBACK_1(GameScene0::assist1, this));
	 Equip[6][2] = MenuItemImage::create("photo/shop/assist/3.jpg",
		"photo/shop/assist/3_1.jpg",
		"photo/shop/assist/3_1.jpg",
		CC_CALLBACK_1(GameScene0::assist2, this));
	 Equip[6][3] = MenuItemImage::create("photo/shop/assist/4.jpg",
		"photo/shop/assist/4_1.jpg",
		"photo/shop/assist/4_1.jpg",
		CC_CALLBACK_1(GameScene0::assist3, this));
	 Equip[6][4] = MenuItemImage::create("photo/shop/assist/5.jpg",
		"photo/shop/assist/5_1.jpg",
		"photo/shop/assist/5_1.jpg",
		CC_CALLBACK_1(GameScene0::assist4, this));
	 Equip[6][5] = MenuItemImage::create("photo/shop/assist/6.jpg",
		"photo/shop/assist/6_1.jpg",
		"photo/shop/assist/6_1.jpg",
		CC_CALLBACK_1(GameScene0::assist5, this));
	 Equip[6][6] = MenuItemImage::create("photo/shop/assist/7.jpg",
		"photo/shop/assist/7_1.jpg",
		"photo/shop/assist/7_1.jpg",
		CC_CALLBACK_1(GameScene0::assist6, this));
	 Equip[6][7] = MenuItemImage::create("photo/shop/assist/8.jpg",
		"photo/shop/assist/8_1.jpg",
		"photo/shop/assist/8_1.jpg",
		CC_CALLBACK_1(GameScene0::assist7, this));
	 Equip[6][8] = MenuItemImage::create("photo/shop/assist/9.jpg",
		"photo/shop/assist/9_1.jpg",
		"photo/shop/assist/9_1.jpg",
		CC_CALLBACK_1(GameScene0::assist8, this));
	for (int i = 0; i <= 8; i++){
		//Equipbuy[6][i] = false;
		if (i <= 3){
			 Equip[6][i]->setPosition(270 + i * 120, 370);
		}
		else {
			 Equip[6][i]->setPosition(270 + (i % 4) * 120, 370 - (i / 4) * 85);
		}
	}

	m_pShopMenu[6] = Menu::create( Equip[6][0],  Equip[6][1],  Equip[6][2],  Equip[6][3],
		 Equip[6][4],  Equip[6][5],  Equip[6][6],  Equip[6][7],
		 Equip[6][8], NULL);

	for (int i = 0; i < 7; i++){
		m_pShopMenu[i]->setPosition(Vec2::ZERO);
		addChild(m_pShopMenu[i], 13);
		m_pShopMenu[i]->setVisible(false);
		m_pBac[i]->setPosition(503, 225);
		//addChild(m_pBac[i], 14);
		m_pBac[i]->setVisible(false);
	}

	////切换按键
	m_pShopMii[0] = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(GameScene0::RecommendMenu, this));
	
	m_pShopMii[1] = MenuItemImage::create("photo/shop/attack.png",
		"photo/shop/attack1.png",
		"photo/shop/attack1.png",
		CC_CALLBACK_1(GameScene0::AttackMenu, this));

	m_pShopMii[2] = MenuItemImage::create("photo/shop/Magic.png",
		"photo/shop/Magic1.png",
		"photo/shop/Magic1.png",
		CC_CALLBACK_1(GameScene0::MagicMenu, this));

	m_pShopMii[3] = MenuItemImage::create("photo/shop/defense.png",
		"photo/shop/defense1.png",
		"photo/shop/defense1.png",
		CC_CALLBACK_1(GameScene0::DefenseMenu, this));

	m_pShopMii[4] = MenuItemImage::create("photo/shop/move.png",
		"photo/shop/move1.png",
		"photo/shop/move1.png",
		CC_CALLBACK_1(GameScene0::MoveMenu, this));

	m_pShopMii[5] = MenuItemImage::create("photo/shop/battle.png",
		"photo/shop/battle1.png",
		"photo/shop/battle1.png",
		CC_CALLBACK_1(GameScene0::BattleMenu, this));

	m_pShopMii[6] = MenuItemImage::create("photo/shop/assist.png",
		"photo/shop/assist1.png",
		"photo/shop/assist1.png",
		CC_CALLBACK_1(GameScene0::AssistMenu, this));

	for (int i = 0; i < 7; i++)
		m_pShopMii[i]->setPosition(166, 328 - 42 * i);

	//记录按下去的
	m_pDownMii = m_pShopMii[0];
	m_pDownMii->setEnabled(false);
	//////关闭按钮
	m_pCloseShop = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(GameScene0::closeShop, this));
	m_pCloseShop->setPosition(870, 400);

	m_ShopMenu = Menu::create(m_pShopMii[0], m_pShopMii[1], m_pShopMii[2], m_pShopMii[3], m_pShopMii[4], m_pShopMii[5], m_pShopMii[6], m_pCloseShop, NULL);
	m_ShopMenu->setPosition(Vec2::ZERO);
	addChild(m_ShopMenu, 12);
	m_ShopMenu->setVisible(false);


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
	m_pMenu = Menu::create(pShopWin, pExitWin, pAttriWin, NULL);
	m_pMenu->setPosition(Vec2::ZERO);
	addChild(m_pMenu, 0);

	//////////////////////////////////////////////////////////////////////////////小地图
	////小地图背景
	Sprite *pSmallMap = Sprite::create("photo/smallMap.png");
	pSmallMap->setPosition(900, 390);
	addChild(pSmallMap, 1);
	//////人物
	if (myChoice == 1)
		myHero = Sprite::create("photo/sBowman.png");
	else if (myChoice == 2)
		myHero = Sprite::create("photo/sSavage.png");
	else
		myHero = Sprite::create("photo/sWizard.png");
	myHero->setPosition(posX,posY);
	addChild(myHero, 2);
	//Vec2(_player->getPosition().x - 500, _player->getPosition().y + 235)

	scheduleUpdate();
	setKeyboardEnabled(true);
	return true;
}

void GameScene0::update(float delta){
	//小地图
	if (m_pGameScene2->Hero.healthPower() <= 0)
		myHero->setVisible(false);
	else {
		myHero->setVisible(true);
		if (posX != m_pGameScene2->PosX() / 10 + 855 || posY != 340 + m_pGameScene2->PosY() / 10) {
			posX = m_pGameScene2->PosX() / 10 + 855;
			posY = 340 + m_pGameScene2->PosY() / 10;
			myHero->setPosition(posX, posY);
		}
	}

	//窗口弹出效果
	if (m_IsPopDialog){
		m_DialogPopTime += delta;
		if (m_DialogPopTime <= 0.3f){
			if (m_DialogPopTime <= 0.2f){
				m_ExitBack->setScale(m_DialogPopTime / 0.2f);
				m_pExitMenu->setScale(m_DialogPopTime / 0.2f);
			}
			else{
				if ((m_DialogPopTime - 0.2f) <= 0.05f){
					m_ExitBack->setScale(1.0f + (m_DialogPopTime - 0.2f) / 0.05f*0.3f);
					m_pExitMenu->setScale(1.0f + (m_DialogPopTime - 0.2f) / 0.05f*0.3f);
				}
				else{
					m_ExitBack->setScale(1.0f + (1.0f - (m_DialogPopTime - 0.25f) / 0.05f)*0.3f);
					m_pExitMenu->setScale(1.0f + (1.0f - (m_DialogPopTime - 0.25f) / 0.05f)*0.3f);
				}
			}
		}
		else{
			m_IsPopDialog = false;
			//m_pExitDialogLayer->setEnable(true);
		}
	}
	///游戏时间更新
	time += delta;
	time_sec = int(time) % 60;
	if (time_sec >= 59){
		number++;
		if (number >= 59){
			time_min++;
			number = 0;
		}
	}

	sprintf(m_Textbuffer, "%d", time_sec);
	m_pTime_secText->setString(m_Textbuffer);

	sprintf(m_Textbuffer, "%d", time_min);
	m_pTime_minText->setString(m_Textbuffer);

	/////技能冷却更新      8   12   18   10   15
	for (int i = 0; i < 5; i++){
		if (!m_SkillUp[i]){
			m_pSkillText[i]->setVisible(true);
			m_pass[i] += delta;
			m_SkillWait[i] = SkillWait[i] - (int(m_pass[i]) % 60);
			sprintf(m_Textbuffer, "%d", m_SkillWait[i]);
			m_pSkillText[i]->setString(m_Textbuffer);
			pSkillMii1[i]->setVisible(true);
		}
		if (m_SkillWait[i] <= 0){
			m_pass[i] = 0;
			m_SkillUp[i] = true;
			//pSkillMii[i]->setEnabled(true);
			pSkillMii1[i]->setVisible(false);
			sprintf(m_Textbuffer, "%d", m_SkillWait[i]);
			m_pSkillText[i]->setString(m_Textbuffer);
			m_pSkillText[i]->setVisible(false);
		}
	}

	//金钱更新
	if (m_pGameScene2->Hero.Money() != m_money){
		m_money = m_pGameScene2->Hero.Money();
		sprintf(m_Textbuffer, "%d", m_money);
		m_pMoneyText->setString(m_Textbuffer);
		m_pMoney2Text->setString(m_Textbuffer);
	}
	if (m_pGameScene2->Hero.tMoney() != t_money){
		t_money = m_pGameScene2->Hero.tMoney();
		sprintf(m_Textbuffer, "%d", t_money);
		t_pMoneyText->setString(m_Textbuffer);
		t_pMoney2Text->setString(m_Textbuffer);
	}

	///////////////////////属性更新

	if (m_kill != m_pGameScene2->Hero.m_kill){
		m_kill = m_pGameScene2->Hero.m_kill;
		sprintf(m_Textbuffer, "%d", m_kill);
		for (int i = 0; i < 3;i++)
			m_pKillText[i]->setString(m_Textbuffer);
	}

	if (m_death != m_pGameScene2->Hero.m_death){
		m_death = m_pGameScene2->Hero.m_death;
		sprintf(m_Textbuffer, "%d", m_death);
		m_pDeathText->setString(m_Textbuffer);

		m_pDeath2Text->setString(m_Textbuffer);
	}

	if (m_health != m_pGameScene2->Hero.totalHealth()){
		m_health = m_pGameScene2->Hero.totalHealth();
		sprintf(m_Textbuffer, "%d", m_health);
		m_pAttri1Text[0]->setString(m_Textbuffer);
		m_pAttri2Text[2]->setString(m_Textbuffer);
	}
	
	if (m_attack != m_pGameScene2->Hero.AttackPower()){
		m_attack = m_pGameScene2->Hero.AttackPower();
		sprintf(m_Textbuffer, "%0.0f", m_attack);
		m_pAttri1Text[1]->setString(m_Textbuffer);
		m_pAttri2Text[0]->setString(m_Textbuffer);
	}

	if (m_power != m_pGameScene2->Hero.Power()){
		m_power = m_pGameScene2->Hero.Power();
		sprintf(m_Textbuffer, "%0.0f", m_power);
		m_pAttri1Text[2]->setString(m_Textbuffer);
		m_pAttri2Text[1]->setString(m_Textbuffer);
	}

	if (armor != m_pGameScene2->Hero.Armor()){
		armor = m_pGameScene2->Hero.Armor();
		sprintf(m_Textbuffer, "%0.0f", armor);
		m_pAttri1Text[3]->setString(m_Textbuffer);
		m_pAttri2Text[4]->setString(m_Textbuffer);
	}

	if (magicDenfence != m_pGameScene2->Hero.MagicDefence()){
		magicDenfence = m_pGameScene2->Hero.MagicDefence();
		sprintf(m_Textbuffer, "%0.0f", magicDenfence);
		m_pAttri1Text[4]->setString(m_Textbuffer);
		m_pAttri2Text[5]->setString(m_Textbuffer);
	}

	if (magicpoint != m_pGameScene2->Hero.MagicPoint()){
		magicpoint = m_pGameScene2->Hero.MagicPoint();
		sprintf(m_Textbuffer, "%d", magicpoint);
		m_pAttri2Text[3]->setString(m_Textbuffer);
	}
	
	if (attackingSpeed != m_pGameScene2->Hero.AttackSpeed()){
		attackingSpeed = m_pGameScene2->Hero.AttackSpeed();
		sprintf(m_Textbuffer, "%0.1f", attackingSpeed);
		m_pAttri2Text[6]->setString(m_Textbuffer);
	}

	if (waitLessen != m_pGameScene2->Hero.WaitLessen()){
		waitLessen = m_pGameScene2->Hero.WaitLessen();
		sprintf(m_Textbuffer, "%0.0f", waitLessen);
		m_pAttri2Text[7]->setString(m_Textbuffer);
	}
	
	if (velocity != m_pGameScene2->Hero.getVelocity()){
		velocity = m_pGameScene2->Hero.getVelocity();
		sprintf(m_Textbuffer, "%0.0f", velocity);
		m_pAttri2Text[9]->setString(m_Textbuffer);
	}
	
	if (healthRecover != m_pGameScene2->Hero.HealthRecover()){
		healthRecover = m_pGameScene2->Hero.HealthRecover();
		sprintf(m_Textbuffer, "%d", healthRecover);
		m_pAttri2Text[10]->setString(m_Textbuffer);
	}
	if (magicpointRecover != m_pGameScene2->Hero.MagicPointRecover()){
		magicpointRecover = m_pGameScene2->Hero.MagicPointRecover();
		sprintf(m_Textbuffer, "%d", magicpointRecover);
		m_pAttri2Text[11]->setString(m_Textbuffer);
	}

	if (armorIgnore != m_pGameScene2->Hero.ArmorIgnore()){
		armorIgnore = m_pGameScene2->Hero.ArmorIgnore();
		sprintf(m_Textbuffer, "%0.0f", armorIgnore);
		m_pAttri2Text[12]->setString(m_Textbuffer);
	}
	if (magicdenfenceIgnore != m_pGameScene2->Hero.MagicDefenseIgnore()){
		magicdenfenceIgnore = m_pGameScene2->Hero.MagicDefenseIgnore();
		sprintf(m_Textbuffer, "%0.0f", magicdenfenceIgnore);
		m_pAttri2Text[13]->setString(m_Textbuffer);
	}
	if (physicBloodSuck != m_pGameScene2->Hero.PhysicBloodSuck()){
		physicBloodSuck = m_pGameScene2->Hero.PhysicBloodSuck();
		sprintf(m_Textbuffer, "%0.0f", physicBloodSuck);
		m_pAttri2Text[14]->setString(m_Textbuffer);
	}
	if (magicBloodSuck != m_pGameScene2->Hero.MagicBloodSuck()){
		magicBloodSuck = m_pGameScene2->Hero.MagicBloodSuck();
		sprintf(m_Textbuffer, "%0.0f", magicBloodSuck);
		m_pAttri2Text[15]->setString(m_Textbuffer);
	}
}
////键盘事件
void GameScene0::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event){
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_Q: {
		if (m_pGameScene2->Hero.healthPower() >= 0) {
			m_SkillUp[0] = false;
			pSkillMii1[0]->setVisible(true);
		}
	}
										break;
	case EventKeyboard::KeyCode::KEY_W: {
		if (m_pGameScene2->Hero.healthPower() >= 0) {
			m_SkillUp[1] = false;
			pSkillMii1[1]->setVisible(false);
		}
	}
										break;
	case EventKeyboard::KeyCode::KEY_E: {
		if (m_pGameScene2->Hero.healthPower() >= 0) {
			m_SkillUp[2] = false;
			pSkillMii1[2]->setVisible(false);
		}
	}
										break;
	case EventKeyboard::KeyCode::KEY_TAB:{      //属性面板1开关
		if (!AttriIsOpen&&!ShopIsOpen){
			AttriIsOpen = true;

			AttriBound(true, false);
			m_pOpAttriMii->setEnabled(false);
			m_pHeroAttriMii->setEnabled(true);
		}
		else if (AttriIsOpen){
			AttriIsOpen = false;
			for (int i = 0; i < 5; i++)
				m_pAttri1Text[i]->setVisible(false);
			m_AttriBack2->setVisible(false);
			AttriBound(false, true);
		}
	}
										 break;
	case EventKeyboard::KeyCode::KEY_P:{      //商店开关
		if (!ShopIsOpen&&!AttriIsOpen){
			ShopIsOpen = true;
			m_pDownMii->setEnabled(true);
			m_pShopMii[0]->setEnabled(false);
			m_pDownMii = m_pShopMii[0];
			m_pDownBac = m_pBac[0];
			m_pDownMenu = m_pShopMenu[0];
			ShopBound(false, true);
		}
		else if (ShopIsOpen){
			ShopIsOpen = false;
			m_pMoney2Text->setVisible(false);
			ShopBound(true, false);
		}
	}
									   break;
	case EventKeyboard::KeyCode::KEY_ENTER:{
		if (ExitIsOpen){
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	}
										   break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:{
		ExitIsOpen = true;
		m_ExitBack->setVisible(true);
		m_pExitMenu->setVisible(true);
		m_ExitBack->setScale(0.0f);
		m_pExitMenu->setScale(0.0f);
		m_IsPopDialog = true;
		m_DialogPopTime = 0.0f;
		BoundTrans(false, true);
	}
	}
}

void GameScene0::transToOp(cocos2d::Ref * pSender){
	AttriTrans(true, false);
}

void GameScene0::transToHero(cocos2d::Ref * pSender){
	AttriTrans(false, true);
}

void GameScene0::closeAttri(cocos2d::Ref * pSender)
{
	for (int i = 0; i < 5; i++)
		m_pAttri1Text[i]->setVisible(false);
	m_AttriBack2->setVisible(false);
	AttriBound(false, true);
}

void GameScene0::openAttri2(cocos2d::Ref * pSender){
	for (int i = 0; i < 16; i++)
		m_pAttri2Text[i]->setVisible(true);
	m_pMenu->setEnabled(false);
	//m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_AttriB1->setVisible(true);
	m_AttriMenu->setVisible(true);
	m_button1->setEnabled(false);
	m_button2->setEnabled(true);
}

void GameScene0::closeAttri2(cocos2d::Ref * pSender) {
	for (int i = 0; i < 6; i++)
		SaleMII[i]->setVisible(false);
	for (int i = 0; i < 16; i++)
		m_pAttri2Text[i]->setVisible(false);
	for (int i = 0; i < 6; i++) {
		if (pEquip[i])
			pEquip[i]->setVisible(false);
	}
	m_pMenu->setEnabled(true);
	//m_pSkillMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_AttriB1->setVisible(false);
	m_AttriB2->setVisible(false);
	m_AttriMenu->setVisible(false);
}


void GameScene0::transTo1(cocos2d::Ref * pSender){
	for (int i = 0; i < 6; i++)
		SaleMII[i]->setVisible(false);
	for (int i = 0; i < 16; i++)
		m_pAttri2Text[i]->setVisible(true);
	m_button1->setEnabled(false);
	m_button2->setEnabled(true);
	m_AttriB1->setVisible(true);
	m_AttriB2->setVisible(false);
	for (int i = 0; i < 6; i++){
		if (pEquip[i])
			pEquip[i]->setVisible(false);
	}
}

void GameScene0::transTo2(cocos2d::Ref * pSender){
	for (int i = 0; i < 16; i++)
		m_pAttri2Text[i]->setVisible(false);
	m_button1->setEnabled(true);
	m_button2->setEnabled(false);
	m_AttriB1->setVisible(false);
	m_AttriB2->setVisible(true);
	for (int i = 0; i < 6; i++){
		if (m_pGameScene2->Hero.equip[i] != -1){
		    EquipNumber[i] = m_pGameScene2->Hero.equip[i];
			n1[i] = EquipNumber[i] /100;
			n2[i] = EquipNumber[i] %100;

			pEquip[i] = Sprite::create("photo/shop/equip.png");
			pEquip[i]->setTextureRect(Rect(49*n2[i],49*(n1[i]-1),48.5,49));
			pEquip[i]->setPosition(300+100*i, 275);
			addChild(pEquip[i], 20);
			pEquip[i]->setVisible(true);
			SaleMII[i]->setVisible(true);		
		}
		else
			break;
	}
}

void GameScene0::openShop(cocos2d::Ref * pSender){
	m_pMoney2Text->setVisible(true);

	m_pDownMii->setEnabled(true);
	m_pShopMii[0]->setEnabled(false);
	m_pDownMii = m_pShopMii[0];
	m_pDownBac = m_pBac[0];
	m_pDownMenu = m_pShopMenu[0];
	ShopBound(false, true);
}

void GameScene0::closeShop(cocos2d::Ref * pSender){
	m_pMoney2Text->setVisible(false);

	ShopBound(true, false);
}

void GameScene0::openExit(cocos2d::Ref * pSender){
	m_ExitBack->setVisible(true);
	m_pExitMenu->setVisible(true);
	m_ExitBack->setScale(0.0f);
	m_pExitMenu->setScale(0.0f);
	m_IsPopDialog = true;
	m_DialogPopTime = 0.0f;
	BoundTrans(false, true);
}

void GameScene0::menuYesCallback(cocos2d::Ref * pSender){
	TransitionScene * reScene = NULL;
	Scene *pScene = MainMenu::createScene();
	reScene = TransitionCrossFade::create(0.8f, pScene);
	Director::getInstance()->replaceScene(reScene);
	//m_IsChangeScene = true;
	/*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif*/
}


void GameScene0::menuNoCallback(cocos2d::Ref * pSender){
	m_ExitBack->setVisible(false);
	m_pExitMenu->setVisible(false);
	BoundTrans(true, false);
}

void GameScene0::AttriBound(bool a, bool b) {
	m_pKillText[2]->setVisible(a);
	m_pDeath2Text->setVisible(a);
	t_pMoneyText->setVisible(a);
	t_pMoney2Text->setVisible(a);
	m_AttriBack1->setVisible(a);
	m_pAttriMenu->setVisible(a);
	BoundTrans(b, a);
}

void GameScene0::AttriTrans(bool a, bool b) {
	for (int i = 0; i < 5; i++)
		m_pAttri1Text[i]->setVisible(b);

	m_pKillText[2]->setVisible(a);
	m_pDeath2Text->setVisible(a);
	t_pMoney2Text->setVisible(a);
	m_pOpAttriMii->setEnabled(b);
	m_pHeroAttriMii->setEnabled(a);
	m_AttriBack1->setVisible(a);
	m_AttriBack2->setVisible(b);

}
void GameScene0::ShopBound(bool a,bool b) {
	BoundTrans(a,b);
	m_pDownBac->setVisible(b);
	m_pDownMenu->setVisible(b);
	m_ShopBack->setVisible(b);
	m_ShopMenu->setVisible(b);
}

void GameScene0::ShopTrans(int i) {
	m_pDownBac->setVisible(false);
	m_pBac[i]->setVisible(true);
	m_pDownBac = m_pBac[i];

	m_pDownMenu->setVisible(false);
	m_pShopMenu[i]->setVisible(true);
	m_pDownMenu = m_pShopMenu[i];
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pShopMii[i];
	m_pDownMii->setEnabled(false);
}

void GameScene0::BoundTrans(bool a, bool b) {
	m_pMenu->setEnabled(a);
	//m_pSkillMenu->setEnabled(a);
	m_pMaskImage->setVisible(b);
}

void GameScene0::RecommendMenu(cocos2d::Ref * pSender){
	ShopTrans(0);
}

void GameScene0::AttackMenu(cocos2d::Ref * pSender){
	ShopTrans(1);
}

void GameScene0::MagicMenu(cocos2d::Ref * pSender){
	ShopTrans(2);
}

void GameScene0::DefenseMenu(cocos2d::Ref * pSender){
	ShopTrans(3);
}

void GameScene0::MoveMenu(cocos2d::Ref * pSender){
	ShopTrans(4);
}

void GameScene0::BattleMenu(cocos2d::Ref * pSender){
	ShopTrans(5);
}

void GameScene0::AssistMenu(cocos2d::Ref * pSender){
	ShopTrans(6);
}

void GameScene0::attack0(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(100);
}
///////////////物品函数
///////////////////卖装备
void GameScene0::sellEquip0(cocos2d::Ref * pSender)
{
	sellEquip(0);
}

void GameScene0::sellEquip1(cocos2d::Ref * pSender)
{
	sellEquip(1);
}

void GameScene0::sellEquip2(cocos2d::Ref * pSender)
{
	sellEquip(2);
}

void GameScene0::sellEquip3(cocos2d::Ref * pSender)
{
	sellEquip(3);
}

void GameScene0::sellEquip4(cocos2d::Ref * pSender)
{
	sellEquip(4);
}

void GameScene0::sellEquip5(cocos2d::Ref * pSender)
{
	sellEquip(5);
}

void GameScene0::sellEquip(int number)
{
	pEquip[number]->setVisible(false);
	m_pGameScene2->Hero.Sale(number, EquipNumber[number]);
	SaleMII[number]->setVisible(false);
}
/////////////买装备
void GameScene0::attack1(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(101);
}

void GameScene0::attack2(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(102);
}

void GameScene0::attack3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(103);
}

void GameScene0::attack4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(104);
}

void GameScene0::attack5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(105);
}

void GameScene0::attack6(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(106);
}

void GameScene0::attack7(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(107);
}

void GameScene0::attack8(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(108);
}

void GameScene0::attack9(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(109);
}

void GameScene0::attack10(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(110);
}

void GameScene0::attack11(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(111);
}

void GameScene0::attack12(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(112);
}

void GameScene0::attack13(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(113);
}

void GameScene0::attack14(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(114);
}

void GameScene0::attack15(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(115);
}

void GameScene0::magic0(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(200);
}

void GameScene0::magic1(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(201);
}

void GameScene0::magic2(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(202);
}

void GameScene0::magic3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(203);
}

void GameScene0::magic4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(204);
}

void GameScene0::magic5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(205);
}

void GameScene0::magic6(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(206);
}

void GameScene0::magic7(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(207);
}

void GameScene0::magic8(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(208);
}

void GameScene0::magic9(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(209);
}

void GameScene0::magic10(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(210);
}

void GameScene0::magic11(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(211);
}

void GameScene0::magic12(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(212);
}

void GameScene0::magic13(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(213);
}

void GameScene0::magic14(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(214);
}

void GameScene0::magic15(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(215);
}

void GameScene0::defense0(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(300);
}

void GameScene0::defense1(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(301);
}

void GameScene0::defense2(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(302);
}

void GameScene0::defense3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(303);
}

void GameScene0::defense4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(304);
}

void GameScene0::defense5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(305);
}

void GameScene0::defense6(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(306);
}

void GameScene0::defense7(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(307);
}

void GameScene0::defense8(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(308);
}

void GameScene0::defense9(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(309);
}

void GameScene0::defense10(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(310);
}

void GameScene0::defense11(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(311);
}

void GameScene0::defense12(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(312);
}

void GameScene0::defense13(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(313);
}

void GameScene0::defense14(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(314);
}

void GameScene0::defense15(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(315);
}


void GameScene0::move0(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(400);
}

void GameScene0::move1(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(401);
}

void GameScene0::move2(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(402);
}

void GameScene0::move3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(403);
}

void GameScene0::move4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(404);
}

void GameScene0::move5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(405);
}

void GameScene0::move6(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(406);
}


void GameScene0::battle0(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(500);
}

void GameScene0::battle1(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(501);
}

void GameScene0::battle2(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(502);
}

void GameScene0::battle3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(503);
}

void GameScene0::battle4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(504);
}

void GameScene0::battle5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(505);
}

void GameScene0::battle6(cocos2d::Ref * pSender)
{
	m_pGameScene2->Hero.Buy(506);
}

void GameScene0::assist0(cocos2d::Ref * pSender)
{
	m_pGameScene2->Hero.Buy(600);
}

void GameScene0::assist1(cocos2d::Ref * pSender)
{
	m_pGameScene2->Hero.Buy(601);
}

void GameScene0::assist2(cocos2d::Ref * pSender)
{
	m_pGameScene2->Hero.Buy(602);
}

void GameScene0::assist3(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(603);
}

void GameScene0::assist4(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(604);
}

void GameScene0::assist5(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(605);
}

void GameScene0::assist6(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(606);
}

void GameScene0::assist7(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(607);
}

void GameScene0::assist8(cocos2d::Ref * pSender){
	m_pGameScene2->Hero.Buy(608);
}

