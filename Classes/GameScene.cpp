#include "GameScene.h"

USING_NS_CC;

float checkTime=0,atkTime=0,advTime=0,minionBorn=0;
float ddl[999] = {0};

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Board::diplay() {
	disBoard->setPosition(500,235);
}
void Board::hide() {
	disBoard->setPosition(-1000,-1000);
}


Sprite* GameScene::createEnemy(int i,int j,int k,Vec2 _pos,std::string str) {
	ObjectBase buf(i, j, k, _pos, str);
	Sprite* cha = buf.getSprite();
	ene.push_back(buf);
	return cha;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}


	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	_tileMap->setPosition(Vec2(0,0));
	addChild(_tileMap, 0);
	
	CenterController.NewMinion(1);
	this->addChild(CenterController.Container()[0].getSprite(), 2);
	CenterController.MoveAndAttack();

	timeTag=LabelTTF::create("0","Arial",24);
	timeTag->setPosition(950, 450);
	this->addChild(timeTag, 1);
	HealthP = LabelTTF::create("0", "Arial", 24);
	HealthP->setPosition(950, 350);
	this->addChild(HealthP, 1);

	Hero.setImage("qian.png");
	Hero = ObjectBase(100, 10, 50, Spawn, "qian.png");
	Hero.setVelocity(100);
	Hero.setSpawnPoint(Vec2(0, 0));
	Hero.getSprite()->setPosition(Vec2(1000, 400));
	this->addChild(Hero.getSprite(), 1);


	bloodView = new ProgressView();
	bloodView->setPosition(ccp(150, 450));
	bloodView->setScale(0.3f);
	bloodView->setBackgroundTexture("bar.png");
	bloodView->setForegroundTexture("blood.png");
	bloodView->setTotalProgress(100);
	bloodView->setCurrentProgress(Hero.healthPower());
	this->addChild(bloodView, 2);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 添加屏幕点击事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();
	//如果不加入此句消息依旧会向下传递  
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
	myListener->onTouchMoved = std::bind(&GameScene::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
	myListener->onTouchEnded = std::bind(&GameScene::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
	dispatcher->addEventListenerWithSceneGraphPriority(myListener, this);

	auto *dispat= Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//键盘被按下时响应
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	//键盘按键被弹回时响应
	dispat->addEventListenerWithSceneGraphPriority(keyListener, this);

	scheduleUpdate();

	return true;
}

void GameScene::update(float delta) {
	Hero.getPosition() = Hero.getSprite()->getPosition();
	bloodView->setCurrentProgress(Hero.healthPower());
	for (int i = 0; i < CenterController.Container().size(); i++) {
		CenterController.Container()[i].getPosition()
			= CenterController.Container()[i].getSprite()->getPosition();
	}

	minionBorn += delta;
	if (minionBorn >= 10) {
		this->addChild(CenterController.NewMinion(1), 2);
		minionBorn = 0;
	}

	advTime += delta;
	if (advTime >= 1) {
		CenterController.CheckAware(&Hero);
		CenterController.Stop();
		CenterController.MoveAndAttack();
		advTime = 0;
	}


	if (Hero.isAttacking()) {
		atkTime += delta;
		if (atkTime > Hero.attackDelay()) {
			Hero.isAttacking() = false;
			atkTime = 0;
		}
	}


	for (int i = 0; i < ene.size(); i++) {
		ene[0].getPosition() = ene[0].getSprite()->getPosition();
		if (ene[i].Dealth()) {
			ddl[i] += delta;
			if (ddl[i] > ene[i].DeadTime) {
				ene[i].revive();
				ddl[i] = 0;
			}
		}
	}

	checkTime += delta;
	if (abs(checkTime - int(checkTime)) < 0.1) {
		sprintf(timeCk, "%d", int(checkTime));
		timeTag->setString(timeCk);
	}
	sprintf(timeCk, "%f", CenterController.Container()[0].getPosition().x);

	HealthP->setString(timeCk);
}

void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Hero.getSprite()->stopAllActions();
	float mindis = 100000;
	int selec = -1;
	for (int i = 0; i < ene.size(); i++) {
		float dis=pTouch->getLocation().distance(ene[i].getPosition());
		if (dis < mindis&&dis<100) {
			selec = i;
		}
	}
	if (selec != -1) {
		Hero.Attack(ene[selec]);
	}
	Hero.Move(pTouch->getLocation());
	//float cost = pTouch->getLocation().distance(Hero.getPosition()) / float(Hero.getVelocity());
	//Hero.getSprite()->runAction(MoveTo::create(3, pTouch->getLocation()));
	return true;
}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_TAB) {
		scoreBoard.diplay();
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_TAB) {
		scoreBoard.hide();
	}
}