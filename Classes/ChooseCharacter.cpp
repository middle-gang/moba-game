#include "ChooseCharacter.h"
#include"GameScene0.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ChooseCharacter::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseCharacter::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharacter::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	m_IsChangeScene = false;

	ChooseHero = 2;

	m_pBowmanIntro = Sprite::create("photo/character/intro1.png");
	m_pBowmanIntro->setPosition(520, 200);
	addChild(m_pBowmanIntro, 1);
	m_pBowmanIntro->setVisible(false);
	
    m_pSavageIntro = Sprite::create("photo/character/intro2.png");
	m_pSavageIntro->setPosition(520, 200);
	addChild(m_pSavageIntro, 1);

	m_pWizardIntro = Sprite::create("photo/character/intro3.png");
	m_pWizardIntro->setPosition(520, 200);
	addChild(m_pWizardIntro, 1);
	m_pWizardIntro->setVisible(false);

	m_pBowmanMII=MenuItemImage::create(
		"photo/character/Bowman0.png",
		"photo/character/Bowman.png",
		"photo/character/Bowman.png",
		CC_CALLBACK_1(ChooseCharacter::BowmanIntro, this));

	m_pSavageMII = MenuItemImage::create(
		"photo/character/Savage0.png",
		"photo/character/Savage.png",
		"photo/character/Savage.png",
		CC_CALLBACK_1(ChooseCharacter::SavageIntro, this));
	m_pSavageMII->setEnabled(false);

	m_pWizardMII = MenuItemImage::create(
		"photo/character/Wizard0.png",
		"photo/character/Wizard.png",
		"photo/character/Wizard.png",
		CC_CALLBACK_1(ChooseCharacter::WizardIntro, this));

	MenuItemImage* ChooseMII = MenuItemImage::create(
		"photo/character/choose0.png",
		"photo/character/choose.png",
		CC_CALLBACK_1(ChooseCharacter::enterGameCallBack, this));
	
	m_pBowmanMII->setPosition(330, 390);
	m_pSavageMII->setPosition(550, 390);
	m_pWizardMII->setPosition(770, 390);
	ChooseMII->setPosition(480, 55);

	Menu *pMenu = Menu::create(m_pBowmanMII, m_pSavageMII,m_pWizardMII,ChooseMII,NULL);
	pMenu->setPosition(Vec2::ZERO);
	addChild(pMenu, 1);

	return true;
}

void ChooseCharacter::BowmanIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(false);
	m_pSavageMII->setEnabled(true);
	m_pWizardMII->setEnabled(true);
	m_pBowmanIntro->setVisible(true);
	m_pSavageIntro->setVisible(false);
	m_pWizardIntro->setVisible(false);
	ChooseHero = 1;
}

void ChooseCharacter::SavageIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(true);
	m_pSavageMII->setEnabled(false);
	m_pWizardMII->setEnabled(true);
	m_pBowmanIntro->setVisible(false);
	m_pSavageIntro->setVisible(true);
	m_pWizardIntro->setVisible(false);
	ChooseHero = 2;
}

void ChooseCharacter::WizardIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(true);
	m_pSavageMII->setEnabled(true);
	m_pWizardMII->setEnabled(false);
	m_pBowmanIntro->setVisible(false);
	m_pSavageIntro->setVisible(false);
	m_pWizardIntro->setVisible(true);
	ChooseHero = 3;
}


void ChooseCharacter::enterGameCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect/button.mp3");

	if (!m_IsChangeScene)
	{
		TransitionScene * reScene = NULL;
		Scene *pScene = GameScene0::createScene();
		reScene = TransitionCrossFade::create(0.8f, pScene);
		Director::getInstance()->replaceScene(reScene);
		m_IsChangeScene = true;
	}
}

void ChooseCharacter::update(float delta)
{
}




