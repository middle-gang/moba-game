#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Object.h"
#include "Blood.h"
#include "MinionController.h"

class Board {
	int kill;
	int death;
	int assist;
	Sprite* disBoard = Sprite::create("board.jpg");
public:
	Board() {
		disBoard->setPosition(-1000, -1000);
	}
	Sprite* BoardSprite() {
		return disBoard;
	}
	void diplay();
	void hide();
};

class GameScene : public cocos2d::Layer
{
	ObjectBase Hero;
	MinionController CenterController;

	cocos2d::TMXTiledMap * _tileMap;
	
	std::vector<ObjectBase> ene;
	std::vector<int> atkList;

	ProgressView* bloodView;
	Board scoreBoard;
	Vec2 Spawn=Vec2::ZERO;
	
	LabelTTF* timeTag;
	LabelTTF* HealthP;
	char timeCk[999];

public:
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();
	Sprite* createEnemy(int i, int j, int k, Vec2 _pos, std::string str);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
	
	virtual void update(float delta);

	//鼠标事件
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);

	//键盘事件
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
