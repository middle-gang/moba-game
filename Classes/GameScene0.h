#ifndef __GAMESCENE0_H__
#define __GAMESCENE0_H__

#include "cocos2d.h"
#include"GameScene2.h"
#include"HUDLayer.h"
//#include "DisplayLayer.h"

using namespace cocos2d;

class GameScene0 : public cocos2d::Scene
{
public:

private:
	GameScene2 *m_pGameScene2;
	HUDLayer *m_pHUDLayer;
	//DisplayLayer *m_pDisplayLayer;
	//CentreLayer *m_pCentreLayer;
	//PropertyBarLayer *m_pPropertyBarLayer;
	//cocos2d::Menu *m_pPropertyMenu;
public:
	static cocos2d::Scene* createScene();


	virtual void GameScene0::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual void update(float delta);
	virtual bool init();

	CREATE_FUNC(GameScene0);

	/*CC_SYNTHESIZE(GameLayer *, _gamelayer, GameLayer);
	CC_SYNTHESIZE(HudLayer *, _hudlayer, HudLayer);*/

};
#endif // __HELLOWORLD_SCENE_H__
#pragma once
#pragma once
