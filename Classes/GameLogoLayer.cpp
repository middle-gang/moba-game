#include "GameLogoLayer.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define LOGOBACKID 100

Scene* GameLogoLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLogoLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLogoLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pLogoBackSpr = Sprite::create("image/logo/logo.png");
	pLogoBackSpr->setPosition(origin.x + visibleSize.width / 2.0f,
		origin.y + visibleSize.height / 2.0f);
	this->addChild(pLogoBackSpr, 0, LOGOBACKID);   //ID便于获取

	m_LogoPassTime = 0.0f;
	m_LogoInTime = 0.6f;
	m_LogoWaitTime = 1.0f;
	m_LogoOutTime = 0.8f;
	m_LogoTime = m_LogoInTime + m_LogoWaitTime + m_LogoOutTime;
	m_IsChangeScene = false;

	scheduleUpdate();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/logo_bgm.mp3");

	return true;
}

void GameLogoLayer::update(float delta)
{
	float rate;
	m_LogoPassTime += delta;
	if (m_LogoPassTime <= m_LogoTime){
		if (m_LogoPassTime <= m_LogoInTime){
			//logo进入的时候
			rate = m_LogoPassTime / m_LogoInTime;
			((Sprite *)getChildByTag(LOGOBACKID))->setOpacity(rate * 255);
		}
		else{
			if ((m_LogoPassTime - m_LogoInTime) <= m_LogoWaitTime){
				//logo等待的时候
				((Sprite *)getChildByTag(LOGOBACKID))->setOpacity(255);
			}
			else{
				//logo出去的时候
				rate = 1.0f - (m_LogoPassTime - (m_LogoInTime + m_LogoWaitTime)) / m_LogoOutTime;
				((Sprite *)getChildByTag(LOGOBACKID))->setOpacity(rate * 255);
			}
		}
	}
	else{
		if (!m_IsChangeScene){
			Scene *pScene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(pScene);
			m_IsChangeScene = true;
		}
	}
}
