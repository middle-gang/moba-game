#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Avene.h"
#include "Help.h"
#include "GameScene.h"
#include "GameScene2.h"

USING_NS_CC;

Scene* Avene::createScene()
{
	return Avene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Avene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	MenuScene1st::init();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto Av55 = MenuItemImage::create(
		"5V51.jpg",
		"5V52.jpg",
		CC_CALLBACK_1(Avene::Av55CallBack, this)
		);
	
	auto Av11 = MenuItemImage::create(
		"1V11.jpg",
		"1V12.jpg",
		CC_CALLBACK_1(Avene::Av11CallBack, this)
	);

	Av55->setPosition(500, 200);
	Av11->setPosition(500, 300);
	auto mu = Menu::create(Av55, Av11, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu,1);
	return true;
}

void Avene::Av55CallBack(cocos2d::Ref* pSender) {
	//auto gameCreate = GameScene::createScene();
	//auto gameCreateChange = TransitionFadeTR::create(1.0f, gameCreate);
	Director::getInstance()->pushScene(GameScene2::createScene());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void Avene::Av11CallBack(cocos2d::Ref* pSender) {

}