
#ifndef __GAMESCENE2_SCENE_H__
#define __GAMESCENE2_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class GameScene2 : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite *_player;
	cocos2d::Sprite *_myCrystal;
	cocos2d::Sprite *_myTower;
	cocos2d::Sprite *_enemyCrystal;
	cocos2d::Sprite *_enemyTower;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	
	void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);

    virtual void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene2);
};

#endif // __HELLOWORLD_SCENE_H__
