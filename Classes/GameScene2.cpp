#include "GameScene2.h"

USING_NS_CC;

float m_atktime = 0, t_atktime = 0, deathtime = 0;
float minionborn = 10,minioncount=0;
float minionMove = 1, minionCnt = 0;
Scene* GameScene2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameScene2::newMinion() {
	Sprite* minionBuf=Sprite::create("ninja.png");
	ObjectBase minionbuf;
	flag[0].minionInit(minionbuf);
	minionbuf.attachToSprite(minionBuf);
	minionBuf->setPosition(flag[0].GetSpawn());
	flag[0].Container().push_back(minionbuf);
	this->addChild(minionBuf, 2);
}

// on "init" you need to initialize your instance
bool GameScene2::init()
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
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2, 200);

	Hero.attachToSprite( _player);
	Hero.healthPower() = 100;
	Hero.getRadium() = 100;
	Hero.AttackPower() = 100;
	Hero.setVelocity(100);
	Hero.setSpawnPoint(Vec2(x,y));

	ValueMap myCrystalPoint = group->getObject("myCrystal");

	x = myCrystalPoint["x"].asFloat();
	y = myCrystalPoint["y"].asFloat();

	_myCrystal = Sprite::create("myCrystal.png");
	_myCrystal->setPosition(Vec2(x, y));
	addChild(_myCrystal, 2, 200);
		
	flag[0].setminionSpawn(Vec2(x, y));
	flag[1].setminionDes(Vec2(x, y));

	ValueMap myTowerPoint = group->getObject("myTower");

	x = myTowerPoint["x"].asFloat();
	y = myTowerPoint["y"].asFloat();

	_myTower = Sprite::create("myTower.png");
	_myTower->setPosition(Vec2(x, y));
	addChild(_myTower, 2, 200);


	ValueMap enemyCrystalPoint = group->getObject("enemyCrystal");

	x = enemyCrystalPoint["x"].asFloat();
	y = enemyCrystalPoint["y"].asFloat();

	_enemyCrystal = Sprite::create("enemyCrystal.png");
	_enemyCrystal->setPosition(Vec2(x, y));
	addChild(_enemyCrystal, 2, 200);

	flag[0].setminionDes(Vec2(x, y));
	flag[1].setminionSpawn(Vec2(x, y));

	ValueMap enemyTowerPoint = group->getObject("enemyTower");

	x = enemyTowerPoint["x"].asFloat();
	y = enemyTowerPoint["y"].asFloat();

	_enemyTower = Sprite::create("enemyTower.png");
	_enemyTower->setPosition(Vec2(x, y));
	addChild(_enemyTower, 2, 200);

    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//setViewpointCenter(_player->getPosition());
    
	Tower.attachToSprite(_enemyTower);
	Tower.healthPower() = 1000;
	Tower.AttackPower() = 20;
	Tower.getRadium() = 200;
	Tower.getPosition() = _enemyTower->getPosition();

    scheduleUpdate();

	_collidable = _tileMap->getLayer("collidable");
    _collidable->setVisible(false);
    
    return true;

}

void GameScene2::update(float delta){
	Hero.getPosition() = Hero.getSprite()->getPosition();	
	for (int i = 0; i < flag[0].Container().size(); i++) {
		flag[0].Container()[i].getPosition() = flag[0].Container()[i].getSprite()->getPosition();
	}

	minioncount += delta;
	if (minioncount > minionborn) {
		minioncount = 0;
		newMinion();
	}
	minionCnt += delta;
	if (flag[0].Container().size() != 0 && minionCnt > minionMove) {
		flag[0].Stop();
		flag[0].CheckAware(&Tower);
		flag[0].MoveAndAttack();
		minionCnt = 0;
	}
	m_atktime += delta;
	if (m_atktime > Hero.attackDelay()) {
		m_atktime = 0;
		Hero.isAttacking() = false;
	}

	t_atktime += delta;
	if (t_atktime > Tower.attackDelay()) {
		t_atktime = 0;
		Tower.isAttacking() = false;
	}

	if (Hero.Death()) {
		deathtime += delta;
		if (deathtime > Hero.DeadTime) {
			Hero.revive();
			deathtime = 0;
		}
	}

	Tower.Attack(Hero);

	//log("%d", Tower.healthPower());

    setViewpointCenter(_player->getPosition());
}

bool GameScene2::onTouchBegan(Touch* touch, Event* event)
{
    log("onTouchBegan");
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target -> convertToNodeSpace(touch->getLocation());
	//log("%f %f", locationInNode.x, locationInNode.y);
	Hero.Move(locationInNode);


	if(locationInNode.distance(Tower.getPosition()) < Hero.getRadium()) {
		Hero.Attack(Tower);
	}

    return true;
}

void GameScene2::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void GameScene2::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
}

void GameScene2::setPlayerPosition(Vec2 position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord =  this->tileCoordFromPosition(position);
	//获得瓦片的Gid
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		
		if (collision == "true") { //碰撞检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	//移动精灵
	_player->setPosition(position);
	//滚动地图
	this->setViewpointCenter(_player->getPosition());
}

Vec2 GameScene2::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x,y);
}

void GameScene2::setViewpointCenter(Vec2 position)
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
