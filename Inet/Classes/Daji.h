#ifndef __DAJI_SCENE_H__
#define __DAJI_SCENE_H__

#include "cocos2d.h"
#include "menuScene1st.h"
using namespace cocos2d;

class Daji : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(Daji);
};

#endif // __DAJI_SCENE_H__

