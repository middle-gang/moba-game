#include "GameScene0.h"

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


	
	m_pHUDLayer = HUDLayer::create();
	addChild(m_pHUDLayer, 2);
	m_pHUDLayer->setVisible(true);

	/*m_pDisplayLayer = DisplayLayer::create();
	addChild(m_pDisplayLayer, 2);
	m_pDisplayLayer->setVisible(true);*/

	m_pGameScene2 = GameScene2::create();
	addChild(m_pGameScene2, 0);
	m_pGameScene2->setVisible(true);

	setKeyboardEnabled(true);

	return true;

}



void GameScene0::update(float delta) {
	//setViewpointCenter(_player->getPosition());

}





