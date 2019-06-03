#include "CentreLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CentreLayer::createScene()
{
	return CentreLayer::create();
}

// on "init" you need to initialize your instance
bool CentreLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
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

	//创建属性界面
	MenuItemImage* pAttriWin = MenuItemImage::create("photo/main/box1.png", "photo/main/box1.png",
		CC_CALLBACK_1(CentreLayer::openAttri, this));
	pAttriWin->setPosition(160, 420);

	m_AttriBack1 = Sprite::create("photo/Attribute/dialog1.png");
	m_AttriBack1->setPosition(500, 236.5);
	addChild(m_AttriBack1, 11);
	m_AttriBack1->setVisible(false);

	m_AttriBack2 = Sprite::create("photo/Attribute/dialog2.png");
	m_AttriBack2->setPosition(500, 236.5);
	addChild(m_AttriBack2, 11);
	m_AttriBack2->setVisible(false);

	m_pOpAttriMii= MenuItemImage::create("photo/PBL/opP_up.png",
		"photo/PBL/opP_down.png",
		"photo/PBL/opP_down.png",
		CC_CALLBACK_1(CentreLayer::transToOp, this));
	m_pOpAttriMii->setPosition(198, 390);
	m_pOpAttriMii->setEnabled(false);

	m_pHeroAttriMii= MenuItemImage::create("photo/PBL/heroP_up.png",
		"photo/PBL/heroP_down.png",
		"photo/PBL/heroP_down.png",
		CC_CALLBACK_1(CentreLayer::transToHero, this));
	m_pHeroAttriMii->setPosition(370, 390);

	m_pCloseAttri=MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(CentreLayer::closeAttri, this));
	m_pCloseAttri->setPosition(870, 400);

	m_pAttriMenu = Menu::create(m_pOpAttriMii, m_pHeroAttriMii, m_pCloseAttri, NULL);
	m_pAttriMenu->setPosition(Vec2::ZERO);
	addChild(m_pAttriMenu, 12);
	m_pAttriMenu->setVisible(false);


	/////////////////////////////创建商店界面
	MenuItemImage * pShopWin = MenuItemImage::create("photo/shop.png", "photo/shop1.png",
		CC_CALLBACK_1(CentreLayer::openShop, this));
	pShopWin->setPosition(930, 200);

	m_ShopBack = Sprite::create("photo/shop/background.png");
	m_ShopBack->setPosition(500, 236.5);
	addChild(m_ShopBack, 11);
	m_ShopBack->setVisible(false);

	///按键
	m_pRecomMii = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(CentreLayer::RecommendMenu, this));
	m_pRecomMii->setPosition(166, 328);

	m_pAttackMii = MenuItemImage::create("photo/shop/attack.png",
		"photo/shop/attack1.png",
		"photo/shop/attack1.png",
		CC_CALLBACK_1(CentreLayer::AttackMenu, this));
	m_pAttackMii->setPosition(166, 286);

	m_pMagicMii = MenuItemImage::create("photo/shop/magic.png",
		"photo/shop/magic1.png",
		"photo/shop/magic1.png",
		CC_CALLBACK_1(CentreLayer::MagicMenu, this));
	m_pMagicMii->setPosition(166, 244);

	m_pDefenseMii = MenuItemImage::create("photo/shop/defense.png",
		"photo/shop/defense1.png",
		"photo/shop/defense1.png",
		CC_CALLBACK_1(CentreLayer::DefenseMenu, this));
	m_pDefenseMii->setPosition(166, 202);

	m_pMoveMii = MenuItemImage::create("photo/shop/recom.png",
		"photo/shop/recom1.png",
		"photo/shop/recom1.png",
		CC_CALLBACK_1(CentreLayer::MoveMenu, this));
	m_pMoveMii->setPosition(166, 160);

	m_pBattleMii = MenuItemImage::create("photo/shop/move.png",
		"photo/shop/move1.png",
		"photo/shop/move1.png",
		CC_CALLBACK_1(CentreLayer::BattleMenu, this));
	m_pBattleMii->setPosition(166, 118);

	m_pAssistMii = MenuItemImage::create("photo/shop/assist.png",
		"photo/shop/assist1.png",
		"photo/shop/assist1.png",
		CC_CALLBACK_1(CentreLayer::AssistMenu, this));
	m_pAssistMii->setPosition(166, 76);

	//记录按下去的
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
	//////
	m_pCloseShop = MenuItemImage::create("photo/exit_up.png",
		"photo/exit_down.png",
		CC_CALLBACK_1(CentreLayer::closeShop, this));
	m_pCloseShop->setPosition(870, 400);

	m_pShopMenu = Menu::create(m_pRecomMii, m_pAttackMii, m_pMagicMii, m_pDefenseMii, m_pMoveMii, m_pBattleMii, m_pAssistMii,m_pCloseShop, NULL);
	m_pShopMenu->setPosition(Vec2::ZERO);
	addChild(m_pShopMenu, 12);
	m_pShopMenu->setVisible(false);


	//退出询问界面
	MenuItemImage* pExitWin = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CentreLayer::openExit, this));
	pExitWin->setPosition(Vec2(origin.x + visibleSize.width - pExitWin->getContentSize().width / 2.0f, origin.y + visibleSize.height - pExitWin->getContentSize().height / 2.0f));

	m_ExitBack = Sprite::create("image/gamescene/exit_dialog.png");
	m_ExitBack->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
	addChild(m_ExitBack, 11);
	m_ExitBack->setVisible(false);

	m_pYesMii = MenuItemImage::create("image/gamescene/yes_btn_up.png", "image/gamescene/yes_btn_down.png",
		CC_CALLBACK_1(CentreLayer::menuYesCallback, this));
	m_pYesMii->setPosition(origin.x + visibleSize.width / 2.0f - 100.0f, origin.y + visibleSize.height / 2.0f - 50);

    m_pNoMii = MenuItemImage::create("image/gamescene/no_btn_up.png", "image/gamescene/no_btn_down.png",
		CC_CALLBACK_1(CentreLayer::menuNoCallback, this));
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
	m_pMenu = Menu::create(pAttriWin,pShopWin,pExitWin,NULL);
	m_pMenu->setPosition(Vec2::ZERO);
	addChild(m_pMenu, 0);

	
	scheduleUpdate();
	return true;
}


void CentreLayer::update(float delta)
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
void CentreLayer::openAttri(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_AttriBack1->setVisible(true);
	m_pAttriMenu->setVisible(true);
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
}

void CentreLayer::transToOp(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(false);
	m_pHeroAttriMii->setEnabled(true);
	m_AttriBack1->setVisible(true);
	m_AttriBack2->setVisible(false);
}

void CentreLayer::transToHero(cocos2d::Ref * pSender)
{
	m_pOpAttriMii->setEnabled(true);
	m_pHeroAttriMii->setEnabled(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(true);
}

void CentreLayer::closeAttri(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_AttriBack1->setVisible(false);
	m_AttriBack2->setVisible(false);
	m_pAttriMenu->setVisible(false);
}

void CentreLayer::openShop(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(false);
	m_pMaskImage->setVisible(true);
	m_ShopBack->setVisible(true);
	m_pShopMenu->setVisible(true);
}

void CentreLayer::closeShop(cocos2d::Ref * pSender)
{
	m_pMenu->setEnabled(true);
	m_pMaskImage->setVisible(false);
	m_ShopBack->setVisible(false);
	m_pShopMenu->setVisible(false);
}

void CentreLayer::RecommendMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pRecomMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::AttackMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAttackMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::MagicMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMagicMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::DefenseMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pDefenseMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::MoveMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pMoveMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::BattleMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pBattleMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::AssistMenu(cocos2d::Ref * pSender)
{
	m_pDownMii->setEnabled(true);
	m_pDownMii = m_pAssistMii;
	m_pDownMii->setEnabled(false);
}

void CentreLayer::openExit(cocos2d::Ref * pSender)
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

void CentreLayer::menuYesCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CentreLayer::menuNoCallback(cocos2d::Ref * pSender)
{
	m_pMenu->setVisible(true);
	m_ExitBack->setVisible(false);
	m_pExitMenu->setVisible(false);
	m_pMaskImage->setVisible(false);
}
