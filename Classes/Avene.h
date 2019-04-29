#ifndef __AVENE_SCENE_H__
#define __AVENE_SCENE_H__

#include "cocos2d.h"
#include "menuScene1st.h"

class Avene : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void Av55CallBack(cocos2d::Ref* pSender);
	void Av11CallBack(cocos2d::Ref* pSender);
	// a selector callback
	// implement the "static create()" method manually
	CREATE_FUNC(Avene);
};

#endif // __AVENE_SCENE_H__