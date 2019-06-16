#ifndef __ChooseType_H__
#define __ChooseType_H__

#include "cocos2d.h"

class ChooseType : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void HCCallBack(cocos2d::Ref* pSender);
	void HHCallBack(cocos2d::Ref* pSender);
	void BackMainMenu(cocos2d::Ref* pSender);
	// a selector callback
	// implement the "static create()" method manually
	CREATE_FUNC(ChooseType);
};

#endif // __AVENE_SCENE_H__#pragma once
