#include "ChooseType.h"
#include "SimpleAudioEngine.h"
#include"ChooseCharacter.h"
#include"MainMenu.h"

USING_NS_CC;

Scene* ChooseType::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseType::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseType::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *backGround = Sprite::create("photo/begin/MoreauStart.png");
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(backGround, 0);

	MenuItemImage *HCMii = MenuItemImage::create("photo/begin/renji.png",
		"photo/begin/renji1.png",
		CC_CALLBACK_1(ChooseType::HCCallBack, this));
	HCMii->setPosition(visibleSize.width / 2, HCMii->getContentSize().height * 4);


	MenuItemImage *HHMii = MenuItemImage::create("photo/begin/lianji.png",
		"photo/begin/lianji1.png",
		CC_CALLBACK_1(ChooseType::HHCallBack, this));
	HHMii->setPosition(visibleSize.width / 2, HHMii->getContentSize().height*2.5);

	MenuItemImage *BackMii=MenuItemImage::create("photo/begin/back.png",
		"photo/begin/back1.png",
		CC_CALLBACK_1(ChooseType::BackMainMenu,this));
	BackMii->setPosition(visibleSize.width / 2, BackMii->getContentSize().height);
	
	Menu* pMainMenu = Menu::create(HCMii,HHMii,BackMii,NULL);
	pMainMenu->setPosition(Vec2::ZERO);
	addChild(pMainMenu, 1);
	return true;
}

void ChooseType::HCCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void ChooseType::HHCallBack(cocos2d::Ref * pSender)
{
	auto startCreate = ChooseCharacter::createScene();
	auto startCreateChange = TransitionFadeTR::create(1.0f, startCreate);
	Director::getInstance()->pushScene(startCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void ChooseType::BackMainMenu(cocos2d::Ref * pSender)
{
	auto startCreate = MainMenu::createScene();
	auto startCreateChange = TransitionFadeTR::create(1.0f, startCreate);
	Director::getInstance()->pushScene(startCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}




