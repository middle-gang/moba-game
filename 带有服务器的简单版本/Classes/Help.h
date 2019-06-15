#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__
#include "menuScene1st.h"

#include "cocos2d.h"
using namespace cocos2d;

class helpScene : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void heroCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(helpScene);
};

#endif // __HELP_SCENE_H__
