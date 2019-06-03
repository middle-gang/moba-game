#ifndef __DisplayLayer_H__
#define __DisplayLayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class DisplayLayer : public cocos2d::Scene
{
private:
	///”Œœ∑ ±º‰
	char m_textContain[100];
	int time_min;
	int time_sec;
	float time;
	int number;

	cocos2d::Label *m_pTime_minText;
	cocos2d::Label *m_pTime_secText;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(DisplayLayer);

};

#endif // __HELLOWORLD_SCENE_H__
#pragma once
