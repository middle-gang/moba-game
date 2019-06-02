//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef __SWA_SCENE_H__
#define __SWA_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class SceneWithAnimation : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
    cocos2d::Sprite *_player;
    cocos2d::Sprite *_myCrystal;
    cocos2d::Sprite *_myTower;
    cocos2d::Sprite *_enemyCrystal;
    cocos2d::Sprite *_enemyTower;
public:
    bool isInBound(int a,int b,int variable);
    bool isLarger(int larger, int smaller);
    
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);
    
    virtual void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(SceneWithAnimation);
};

#endif // __HELLOWORLD_SCENE_H__
