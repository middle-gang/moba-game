#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "menuScene1st.h"

class SettingScene : public MenuScene1st
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void MusicCallback(cocos2d::Ref* pSender);
	void MusicUpCallback(cocos2d::Ref* pSender);
	void MusicDownCallback(cocos2d::Ref* pSender);
	// a selector callback
	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);
};

#endif // __SETTING_SCENE_H__
