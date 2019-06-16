#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include"ChooseType.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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

	MenuItemImage *pStartMii = MenuItemImage::create("photo/begin/start.png",
		"photo/begin/start1.png",
		CC_CALLBACK_1(MainMenu::StartCallback, this));
	pStartMii->setPosition(visibleSize.width/2,pStartMii->getContentSize().height*2.5);

	MenuItemImage *pCloseMii = MenuItemImage::create("photo/begin/exit.png",
		"photo/begin/exit1.png",
		CC_CALLBACK_1(MainMenu::StartCallback, this));
	pCloseMii->setPosition(visibleSize.width / 2, pCloseMii->getContentSize().height);
	
	//MenuItemImage *pCloseMii=MenuItemImage::create("photo/")

	Menu* pMainMenu= Menu::create(pStartMii, pCloseMii,NULL);
	pMainMenu->setPosition(Vec2::ZERO);
	addChild(pMainMenu, 1);
	return true;
}


void MainMenu::StartCallback(cocos2d::Ref * pSender)
{
	auto startCreate = ChooseType::createScene();
	auto startCreateChange = TransitionFadeTR::create(1.0f, startCreate);
	Director::getInstance()->pushScene(startCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void MainMenu::CloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	exit(0);
#endif

}

