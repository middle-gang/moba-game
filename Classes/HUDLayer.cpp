#include "HUDLayer.h"
#include "SimpleAudioEngine.h"

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


	/////////////////////////////创建商店界面
	ShopIsOpen = false;
	MenuItemImage * pShopWin = MenuItemImage::create("photo/shop.png", "photo/shop1.png",
		CC_CALLBACK_1(HUDLayer::openShop, this));
	pShopWin->setPosition(930, 200);

	m_ShopBack = Sprite::create("photo/shop/background.png");
	m_ShopBack->setPosition(500, 236.5);
	addChild(m_ShopBack, 11);
	m_ShopBack->setVisible(false);

	///按键
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

	m_pMagicMii = MenuItemImage::create("photo/shop/magic.png",
		"photo/shop/magic1.png",
		"photo/shop/magic1.png",
		CC_CALLBACK_1(HUDLayer::MagicMenu, this));
	m_pMagicMii->setPosition(166, 244);

	m_pDefenseMii = MenuItemImage::create("photo/shop/defense.png",
		"photo/shop/defense1.png",
		"photo/shop/defense1.png",
		CC_CALLBACK_1(HUDLayer::DefenseMenu, this));
	m_pDefenseMii->setPosition(166, 202);

	m_pMoveMii = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(HUDLayer::MoveMenu, this));
	m_pMoveMii->setPosition(166, 160);

	m_pBattleMii = MenuItemImage::create("photo/shop/move.png",
		"photo/shop/move1.png",
		"photo/shop/move1.png",
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
	//////
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

	pSkill1Mii = MenuItemImage::create("photo/Arthur/Arthur1.png", "photo/Arthur/Arthur1-2.png", "photo/Arthur/Arthur1-2.png",
		CC_CALLBACK_1(HUDLayer::Skill1, this));
	pSkill1Mii->setPosition(70, 150);

	pSkill2Mii = MenuItemImage::create("photo/Arthur/Arthur2.png", "photo/Arthur/Arthur2-2.png", "photo/Arthur/Arthur2-2.png",
		CC_CALLBACK_1(HUDLayer::Skill2, this));
	pSkill2Mii->setPosition(120, 90);

	pSkill3Mii = MenuItemImage::create("photo/Arthur/Arthur3.png", "photo/Arthur/Arthur3-2.png", "photo/Arthur/Arthur3-2.png",
		CC_CALLBACK_1(HUDLayer::Skill3, this));
	pSkill3Mii->setPosition(70, 30);


	m_pSkillMenu = Menu::create(pSkill1Mii, pSkill2Mii, pSkill3Mii, pAttackMii, pRecoverMii, pCureMii, NULL);
	m_pSkillMenu->setPosition(Vec2::ZERO);
	addChild(m_pSkillMenu, 1);


	//属性数值显示
	Label* m_pAssist = Label::createWithTTF("0", "fonts/msyh.ttc", 23);
	m_pAssist->setPosition(200, 435);
	addChild(m_pAssist, 3);

	sprintf(m_Textbuffer, "%d", m_kill);
	m_pKillText = Label::createWithTTF(m_Textbuffer, "fonts/msyh.ttc", 23);
	m_pKillText->setPosition(160, 435);
	addChild(m_pKillText, 3);

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
	m_pMenu->setEnabled(false);
	m_pSkillMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_ShopBack->setVisible(true);
	m_pShopMenu->setVisible(true);
}

void HUDLayer::closeShop(cocos2d::Ref * pSender)
{
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
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif
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
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::AttackMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAttackMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::MagicMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMagicMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::DefenseMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pDefenseMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::MoveMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMoveMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::BattleMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pBattleMii;
	m_pDownMii->setEnabled(false);
}

void HUDLayer::AssistMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAssistMii;
	m_pDownMii->setEnabled(false);
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



