#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__

#include "cocos2d.h"
#include "menuScene1st.h"

using namespace cocos2d;

class heroScene : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void Arthur(cocos2d::Ref* pSender);
	void Houyi(cocos2d::Ref* pSender);
	void Daji(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(heroScene);
};

#endif // __HERO_SCENE_H__

