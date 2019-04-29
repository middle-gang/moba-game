#include "Help.h"
#include "hero.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* helpScene::createScene()
{
	return helpScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool helpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	MenuScene1st::init();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	auto heroitem = MenuItemImage::create("Hero.jpg",
										  "Hero.jpg",
	                                       CC_CALLBACK_1(helpScene::heroCallback,this));
	heroitem->setPosition(500, 235);

	// create menu, it's an autorelease object
	auto menu = Menu::create(heroitem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void helpScene::heroCallback(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
	auto heroCreate = heroScene::createScene();
	auto heroCreateChange = TransitionFadeTR::create(1.0f, heroCreate);
	Director::getInstance()->pushScene(heroCreateChange);
}
