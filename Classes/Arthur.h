#ifndef __ARTHUR_SCENE_H__
#define __ARTHUR_SCENE_H__

#include "cocos2d.h"
#include "menuScene1st.h"
using namespace cocos2d;

class Arthur : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(Arthur);
};

#endif // __ARTHUR_SCENE_H__

