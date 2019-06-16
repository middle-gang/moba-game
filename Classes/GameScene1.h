
#ifndef __GAMESCENE2_SCENE_H__
#define __GAMESCENE2_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Object.h"
#include "MinionController.h"
#include "HeroObj.h"
#include <thread>

class GameScene2 : public cocos2d::Layer
{
	char Textbuffer[100];
	int n_level;
	cocos2d::Label *_myLevel;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite *_player,*EneSpr;
	cocos2d::Sprite *_myCrystal;
	cocos2d::Sprite *_myTower;
	cocos2d::Sprite *_enemyCrystal;
	cocos2d::Sprite *_enemyTower;

	MinionController flag[2];

public:
	HeroObj Hero;
	HeroObj Opponent;
	ObjectBase Tower[2];
	ObjectBase Crystal[2];

public:
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
	
	//kono 键盘监听 da
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	//kono 触摸监听 da
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	
	void setPlayerPosition(cocos2d::Vec2 position); //设置玩家的位置
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);//转化成瓦片坐标
    void setViewpointCenter(cocos2d::Vec2 position);//设置屏幕中央

	void newCloseMinion(int i);		//产生新的近战小兵
	void newDistantMinion(int i);	//产生新的远程兵
	void playMove();				//根据A*寻路产生的链表进行移动
	void TowerInit(int i,Sprite*& spr);//初始化塔
	void CrystalInit(int i,Sprite*& spr);

	//万恶之源
    virtual void update(float delta);

	// implement the "static create()" method manually
    CREATE_FUNC(GameScene2);
};

#endif // __HELLOWORLD_SCENE_H__
