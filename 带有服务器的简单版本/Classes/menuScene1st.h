#ifndef __MENUSCENE1STSCENE_H__
#define __MENUSCENE1STSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class MenuScene1st : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void homeCallback(cocos2d::Ref* pSender);
	void backCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene1st);
};

#endif // __MENUSCENE1STSCENE_SCENE_H__

