#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "MenuScene1st.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public MenuScene1st{
	cocos2d::CCSprite* MySprite, * charQ;
	float Sspeed = 60;
	CCSprite* MenuTab = CCSprite::create("HelloWorld.png");
	Vec2 des, now;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//鼠标事件
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);
	//键盘事件
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__
