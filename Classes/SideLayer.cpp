#include "SideLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SideLayer::createScene()
{
	return SideLayer::create();
}

// on "init" you need to initialize your instance
bool SideLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Ð¡µØÍ¼
	Sprite *pSmallMap = Sprite::create("photo/smallMap.png");
	pSmallMap->setPosition(900, 390);
	addChild(pSmallMap, 1);

	
	return true;
}


