#include "HeroInstuct.h"
#include "Help.h"
#include "Arthur.h"
#include "Houyi.h"
#include "Daji.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* heroScene::createScene()
{
	return heroScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool heroScene::init()
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

	auto Arthur = MenuItemImage::create("Arthur.png",
		"Arthur.png",
		CC_CALLBACK_1(heroScene::Arthur, this));
	auto Houyi = MenuItemImage::create("Houyi.png",
		"Houyi.png",
		CC_CALLBACK_1(heroScene::Houyi, this));
	auto Daji = MenuItemImage::create("Daji.png",
		"Daji.png",
		CC_CALLBACK_1(heroScene::Daji, this));

	Arthur->setPosition(200, 235);
	Houyi->setPosition(500, 235);
	Daji->setPosition(800, 235);

	// create menu, it's an autorelease object
	auto menu = Menu::create(Arthur,Houyi,Daji, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label1 = Label::createWithTTF("Arthur", "fonts/Marker Felt.ttf", 40);
	if (label1 == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label1->setPosition(200, 300);
		label1->setColor(Color3B::MAGENTA);
		// add the label as a child to this layer
		this->addChild(label1,1);
	}

	auto label2 = Label::createWithTTF("HouYi", "fonts/Marker Felt.ttf", 40);
	if (label2 == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label2->setPosition(500, 300);
		label2->setColor(Color3B::MAGENTA);
		// add the label as a child to this layer
		this->addChild(label2, 1);
	}

	auto label3 = Label::createWithTTF("DaJi", "fonts/Marker Felt.ttf", 40);
	if (label3 == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label3->setPosition(800, 300);
		label3->setColor(Color3B::MAGENTA);
		// add the label as a child to this layer
		this->addChild(label3, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("Entrance.png");
	if (sprite == nullptr)
	{
		problemLoading("'Entrance.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	return true;
}

void heroScene::Arthur(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ArthurMusic.wav", false);
	Director::getInstance()->pushScene(Arthur::createScene());
}
void heroScene::Houyi(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("HouyiMusic.wav", false);
	Director::getInstance()->pushScene(Houyi::createScene());
}
void heroScene::Daji(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("DajiMusic.wav", false);
	Director::getInstance()->pushScene(Daji::createScene());
}
