#include "GameScene2.h"

USING_NS_CC;

float m_atktime = 0, mt_atktime = 0,et_atktime=0, deathtime = 0;
float minionborn = 10,minioncount=0;
float minioncount1 = 0;
float minionMove = 1, minionCnt = 0,minionCnt1=0;
bool reverse = false;
bool checkAlive[2][999];
Vec2 prelocation;
//std::map<ObjectBase, bool> minionAlive;

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

void GameScene2::newMinion(int i) {
	Sprite* minionBuf = Sprite::createWithSpriteFrameName("CloseWarriorRun1.png");
	ObjectBase minionbuf;
	flag[i].minionInit(minionbuf);
	minionbuf.attachToSprite(minionBuf);
	minionBuf->setPosition(flag[i].GetSpawn());
	minionbuf.initBloodScale();
	this->addChild(minionbuf.BloodView, 1);
	flag[i].Container().push_back(minionbuf);
	//minionAlive[*(flag[i].Container().end() - 1)] = true;
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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BowmanRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CloseWarriorRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DistantWarriorWarriorRun.plist");

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::createWithSpriteFrameName("BowmanRun1.png");
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2, 200);

	Hero.attachToSprite( _player);
	Hero.healthPower() = 100;
	Hero.getRadium() = 100;
	Hero.AttackPower() = 100;
	Hero.setVelocity(100);
	Hero.setSpawnPoint(Vec2(x,y));
	Hero.initBloodScale();
	std::string HeroFrameName = "CloseWarriorRun";
	Hero.setFrame(HeroFrameName);
	addChild(Hero.BloodView, 2);

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
    
	Tower[0].attachToSprite(_enemyTower);
	Tower[0].healthPower() = 1000;
	Tower[0].AttackPower() = 50;
	Tower[0].getRadium() = 150;
	Tower[0].setAttackingSpeed(1.5);
	Tower[0].setMoveablity(false);
	Tower[0].getPosition() = _enemyTower->getPosition();

	Tower[1].attachToSprite(_myTower);
	Tower[1].healthPower() = 1000;
	Tower[1].AttackPower() = 50;
	Tower[1].getRadium() = 150;
	Tower[1].setAttackingSpeed(1.5);
	Tower[0].setMoveablity(false);
	Tower[1].getPosition() = _myTower->getPosition();


	scheduleUpdate();
	/*this->schedule(schedule_selector(GameScene2::timer1));
	this->schedule(schedule_selector(GameScene2::timer2));*/

	_collidable = _tileMap->getLayer("collidable");
    _collidable->setVisible(false);
    
    return true;

}

void GameScene2::update(float delta){
	Hero.getPosition() = Hero.getSprite()->getPosition();
	
	if (_player->getPosition() == prelocation) {
		_player->stopAllActions();
	}
	prelocation = _player->getPosition();

	Hero.BloodView->setPosition(Vec2(Hero.getPosition().x, Hero.getPosition().y + 15));
	for (int i = 0; i < flag[0].Container().size(); i++) {
		/*if (flag[0].Container()[i].healthPower() <= 0) {
			minionAlive[flag[0].Container()[i]] = false;
		}*/
		if (checkAlive[0][i]) continue;
		if (flag[0].Container()[i].healthPower() <= 0&&!checkAlive[0][i]) {
			this->removeChild(flag[0].Container()[i].getSprite());
			checkAlive[0][i] = true;
			continue;
		}

		if (flag[0].Container()[i].isAttacking()) {
			flag[0].Judge(i, delta);
		}
		flag[0].Container()[i].getPosition() = flag[0].Container()[i].getSprite()->getPosition();
		flag[0].Container()[i].BloodView->setPosition(Vec2(flag[0].Container()[i]
			.getPosition().x, flag[0].Container()[i].getPosition().y + 15));
		flag[0].Container()[i].BloodView->setCurrentProgress(flag[0].Container()[i].healthPower());

	}

	for (int i = 0; i < flag[1].Container().size() ; i++) {
		if (checkAlive[1][i]) continue;
		if (flag[1].Container()[i].healthPower() <= 0&&!checkAlive[1][i]) {
			this->removeChild(flag[1].Container()[i].getSprite());
			checkAlive[1][i] = true;
			continue;
		}

		if (flag[1].Container()[i].isAttacking()) {
			flag[1].Judge(i, delta);
		}
		flag[1].Container()[i].getPosition() = flag[1].Container()[i].getSprite()->getPosition();
		flag[1].Container()[i].BloodView->setPosition(Vec2(flag[1].Container()[i]
			.getPosition().x, flag[1].Container()[i].getPosition().y + 15));
		flag[1].Container()[i].BloodView->setCurrentProgress(flag[1].Container()[i].healthPower());
	}

	minionCnt += delta;
	if (minionCnt > 0.2&&reverse) {
		for (int i = 0; i < flag[0].Container().size(); i++) {
			if (flag[0].Container()[i].healthPower() <= 0) continue;
			bool ck = false;
			bool tarck = false;
			ObjectBase* target;
			float MiniPath = 1500;
			for (int j = 0; j < flag[1].Container().size(); j++) {
				if (flag[1].Container()[j].healthPower() <= 0) continue;
				float dis = flag[0].Container()[i].getPosition().distance(flag[1].Container()[j].getPosition());
				if (dis < 200 && dis < MiniPath) {
					MiniPath = dis;
					flag[0].getPlan(i) = flag[1].Container()[j].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &flag[1].Container()[j];
						tarck = true;
					}
					ck = true;
				}
			}
			if (!ck) {
				flag[0].getPlan(i) = flag[0].GetDes();
			}
			if (tarck) {
				flag[0].Container()[i].Attack(*target);
				reverse = !reverse;
			}
		}

		for (int i = 0; i < flag[1].Container().size(); i++) {
			if (flag[1].Container()[i].healthPower() <= 0) continue;
			bool ck = false;
			bool tarck = false;
			float MiniPath = 1500;
			ObjectBase* target;
			for (int j = 0; j < flag[0].Container().size(); j++) {
				if (flag[0].Container()[j].healthPower() <= 0) continue;
				float dis = flag[1].Container()[i].getPosition().distance(flag[0].Container()[j].getPosition());
				if (dis < 200 && dis < MiniPath) {
					MiniPath = dis;
					flag[1].getPlan(i) = flag[0].Container()[j].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &flag[0].Container()[j];
						tarck = true;
					}
					ck = true;
				}
			}
			if (!ck) {
				flag[1].getPlan(i) = flag[1].GetDes();
			}
			if (tarck) {
				flag[1].Container()[i].Attack(*target);
			}
		}

		flag[0].MoveToTarget();
		flag[1].MoveToTarget();

		minionCnt = 0;
	}

	if (minionCnt > 0.2&&!reverse) {
		for (int i = 0; i < flag[1].Container().size(); i++) {
			if (flag[1].Container()[i].healthPower() <= 0) continue;
			bool ck = false;
			bool tarck = false;
			float MiniPath = 1500;
			ObjectBase* target;
			for (int j = 0; j < flag[0].Container().size() ; j++) {
				if (flag[0].Container()[j].healthPower() <= 0) continue;
				float dis = flag[1].Container()[i].getPosition().distance(flag[0].Container()[j].getPosition());
				if (dis < 200 && dis < MiniPath) {
					MiniPath = dis;
					flag[1].getPlan(i) = flag[0].Container()[j].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &flag[0].Container()[j];
						tarck = true;
					}
					ck = true;
				}
			}
			if (!ck) {
				flag[1].getPlan(i) = flag[1].GetDes();
				reverse = !reverse;
			}
			if (tarck) {
				flag[1].Container()[i].Attack(*target);
			}
		}

		for (int i = 0; i < flag[0].Container().size(); i++) {
			if (flag[0].Container()[i].healthPower() <= 0) continue;
			bool ck = false;
			bool tarck = false;
			ObjectBase* target;
			float MiniPath = 1500;
			for (int j = 0; j < flag[1].Container().size(); j++) {
				if (flag[1].Container()[j].healthPower() <= 0) continue;
				float dis = flag[0].Container()[i].getPosition().distance(flag[1].Container()[j].getPosition());
				if (dis < 200 && dis < MiniPath) {
					MiniPath = dis;
					flag[0].getPlan(i) = flag[1].Container()[j].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &flag[1].Container()[j];
						tarck = true;
					}
					ck = true;
				}
			}
			if (!ck) {
				flag[0].getPlan(i) = flag[0].GetDes();
			}
			if (tarck) {
				flag[0].Container()[i].Attack(*target);
			}
		}

		flag[0].MoveToTarget();
		flag[1].MoveToTarget();

		minionCnt = 0;
		reverse = !reverse;
	}


	minioncount += delta;
	if (minioncount > minionborn) {
		minioncount = 0;
		newMinion(0);
		newMinion(1);
	}

	if (Hero.isAttacking()) {
		m_atktime += delta;
		Hero.Judge(m_atktime);
	}

	if (Tower[0].isAttacking()) {
		mt_atktime += delta;
		Tower[0].Judge(mt_atktime);
	}

	if (Tower[1].isAttacking()) {
		et_atktime += delta;
		Tower[1].Judge(et_atktime);
	}

	if (Hero.Death()) {
		deathtime += delta;
		if (deathtime > Hero.DeadTime) {
			Hero.revive();
			deathtime = 0;
		}
	}

	setViewpointCenter(_player->getPosition());
}

bool GameScene2::onTouchBegan(Touch* touch, Event* event)
{
    log("onTouchBegan");

    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target -> convertToNodeSpace(touch->getLocation());
	//log("%f %f", locationInNode.x, locationInNode.y);
	Hero.Move(locationInNode);

	if(locationInNode.distance(Tower[0].getPosition()) < Hero.getRadium()) {
		Hero.Attack(Tower[0]);
	}

	/*Animation * animation = Animation::create();
	for (int i = 1; i <= 6; i++) {
		__String * frameName = __String::createWithFormat("CloseWarriorRun%d.png", i);
		log("frameName = %s", frameName->getCString());
		SpriteFrame * spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}

	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);     //动画执行后还原初始状态

	Animate * action = Animate::create(animation);
	this->_player->runAction(RepeatForever::create(action));*/

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
