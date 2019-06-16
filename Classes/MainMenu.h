#ifndef __MainMenu_H__
#define __MainMenu_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//// a selector callback
	void StartCallback(cocos2d::Ref* pSender);
	void CloseCallback(cocos2d::Ref* pSender);
	//void mymenuitemcallback(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};
#endif // __MainMenu_H__
#pragma once

