#ifndef __BottemLayer_H__
#define __BottemLayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class BottemLayer : public cocos2d::Scene
{
private:
	cocos2d::MenuItemImage *pAttackMii;
	cocos2d::MenuItemImage *pRecoverMii;
	cocos2d::MenuItemImage *pCureMii;

	cocos2d::MenuItemImage *pSkill1Mii;
	cocos2d::MenuItemImage *pSkill2Mii;
	cocos2d::MenuItemImage *pSkill3Mii;

	cocos2d::Menu *m_pSkillMenu;
	
public:
	void Skill1(cocos2d::Ref* pSender);
	void Skill2(cocos2d::Ref* pSender);
	void Skill3(cocos2d::Ref* pSender);

	void attack(cocos2d::Ref* pSender);
	void recover(cocos2d::Ref* pSender);
	void cure(cocos2d::Ref* pSender);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(BottemLayer);
};

#endif // __HELLOWORLD_SCENE_H__
#pragma once
#pragma once
#pragma once
