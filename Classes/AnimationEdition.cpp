#include "AnimationEdition.h"

USING_NS_CC;
bool face=true;
Vec2 preLocation=Vec2(-100,-100);

Scene* SceneWithAnimation::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneWithAnimation::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneWithAnimation::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
    addChild(_tileMap,0,100);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BowmanRun.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CloseWarriorRun.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DistantWarriorWarriorRun.plist");
    
    TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
    ValueMap spawnPoint = group->getObject("hero");
    
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
    
    _player = Sprite::createWithSpriteFrameName("CloseWarriorRun1.png");
    _player->setPosition(Vec2(x,y));
    addChild(_player, 2, 200);
    
    ValueMap myCrystalPoint = group->getObject("myCrystal");
    
    x = myCrystalPoint["x"].asFloat();
    y = myCrystalPoint["y"].asFloat();
    
    _myCrystal = Sprite::create("myCrystal.png");
    _myCrystal->setPosition(Vec2(x,y));
    addChild(_myCrystal, 2, 200);
    
    ValueMap myTowerPoint = group->getObject("myTower");
    
    x = myTowerPoint["x"].asFloat();
    y = myTowerPoint["y"].asFloat();
    
    _myTower = Sprite::create("myTower.png");
    _myTower->setPosition(Vec2(x,y));
    addChild(_myTower, 2, 200);
    
    ValueMap enemyCrystalPoint = group->getObject("enemyCrystal");
    
    x = enemyCrystalPoint["x"].asFloat();
    y = enemyCrystalPoint["y"].asFloat();
    
    _enemyCrystal = Sprite::create("enemyCrystal.png");
    _enemyCrystal->setPosition(Vec2(x,y));
    addChild(_enemyCrystal, 2, 200);
    
    ValueMap enemyTowerPoint = group->getObject("enemyTower");
    
    x = enemyTowerPoint["x"].asFloat();
    y = enemyTowerPoint["y"].asFloat();
    
    _enemyTower = Sprite::create("enemyTower.png");
    _enemyTower->setPosition(Vec2(x,y));
    addChild(_enemyTower, 2, 200);
    
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    //setViewpointCenter(_player->getPosition());
    
    scheduleUpdate();
    
    _collidable = _tileMap->getLayer("collidable");
    _collidable->setVisible(false);        //把collidable层设为不可见
    
    return true;
    
}

void SceneWithAnimation::update(float delta)
{
    setViewpointCenter(_player->getPosition());
    if(_player->getPosition()==preLocation){
        _player->stopAllActions();
    }
    preLocation=_player->getPosition();
}

bool SceneWithAnimation::onTouchBegan(Touch* touch, Event* event)
{
    log("onTouchBegan");
    
    _player->stopAllActions();
    
    //    _player->runAction(FlipX::create(_player->getPosition().x-touch->getLocation().x<0));
    
    Animation * animation = Animation::create();
    for(int i=1;i<=6;i++){
        __String * frameName = __String::createWithFormat("CloseWarriorRun%d.png",i);
        log("frameName = %s",frameName->getCString());
        SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
        animation->addSpriteFrame(spriteFrame);
    }
    
    animation->setDelayPerUnit(0.08f);
    animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态
    
    Animate * action = Animate::create(animation);
    this->_player->runAction(RepeatForever::create(action));
    
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target -> convertToNodeSpace(touch->getLocation());
    
    Vec2 tileCoord =  this->tileCoordFromPosition(locationInNode);
    int tileGid = _collidable->getTileGIDAt(tileCoord);
    if (tileGid > 0) {
        Value prop = _tileMap->getPropertiesForGID(tileGid);
        ValueMap propValueMap = prop.asValueMap();
        
        std::string collision = propValueMap["Collidable"].asString();
        
        if (collision == "true") { //碰撞检测成功
            return true;
        }
    }
    else{
        auto curveMove = MoveTo::create(1.5f,locationInNode);
        this->_player->runAction(curveMove);
    }
    
    return true;
}

void SceneWithAnimation::onTouchMoved(Touch *touch, Event *event)
{
    log("onTouchMoved");
}

void SceneWithAnimation::onTouchEnded(Touch *touch, Event *event)
{
    log("onTouchEnded");
    
}

Vec2 SceneWithAnimation::tileCoordFromPosition(Vec2 pos)
{
    int x = pos.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
    return Vec2(x,y);
}

void SceneWithAnimation::setViewpointCenter(Vec2 position)
{
    log("setViewpointCenter");
    
    log("position (%f ,%f) ",position.x,position.y);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //可以防止，视图左边超出屏幕之外。
    int x = MAX(position.x, visibleSize.width / 2);
    int y = MAX(position.y, visibleSize.height / 2);
    //可以防止，视图右边超出屏幕之外。
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
            - visibleSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
            - visibleSize.height/2);
    
    //屏幕中心点
    Vec2 pointA = Vec2(visibleSize.width/2, visibleSize.height/2);
    //使精灵处于屏幕中心，移动地图目标位置
    Vec2 pointB = Vec2(x, y);
    log("目标位置 (%f ,%f) ",pointB.x,pointB.y);
    
    //地图移动偏移量
    Vec2 offset =pointA - pointB;
    log("offset (%f ,%f) ",offset.x, offset.y);
    this->setPosition(offset);
    
}
