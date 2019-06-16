#ifndef __GAMELOGO_SCENE_H__
#define __GAMELOGO_SCENE_H__

#include "cocos2d.h"

class GameLogoLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);
	//// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);
	//void mymenuitemcallback(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameLogoLayer);
private:
	float m_LogoPassTime;
	float m_LogoTime;
	float m_LogoInTime;
	float m_LogoWaitTime;
	float m_LogoOutTime;
	bool m_IsChangeScene;
};

#endif // __GAMELOGO_SCENE_H__
#pragma once
