#include "GameScene2.h"
#include "HelloWorldScene.h"

#include"GlobalVal.h"
#include "Astar.h"


USING_NS_CC;

float m_atktime = 0, mt_atktime = 0;
float e_atktime = 0, et_atktime = 0;
float mc_atktime = 0, ec_atktime = 0;
float deathtime = 0, edeathtime = 0;
float eneHome = 1, myHome = 1;
float minionborn = 30,minioncount1=1;
float minioncount2 = 1.5,minioncount3=2, minioncount4 = 2.5, minioncount5 = 3;
float minionMove = 1, minionCnt = 0,minionCnt1=0;
float animeEnded[2][999];
float animeFinish[2][999];
float backSpawn = 0, ebackSpawn = 0;
float movingJud = 0;
float moving;
bool tiledMap[32][32];
bool reverse = false;
bool checkAlive[2][999];
bool cryInit[2] = { false,false };
Vec2 prelocation,eprelocation;
int moveStep = 0;
bool isRight = true;
std::list<PointCk *> pathFound;
int minionNum0 = 0;
int minionNum1 = 0;
//std::map<ObjectBase, bool> minionAlive;
Astar ast;
HeroObj* heroObj, *eneObj;
ObjectBase* MyTower, *EneTower;
MinionController* mMinion, *eMinion;
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

void GameScene2::TowerInit(int i,Sprite*& spr) {
	Tower[i].attachToSprite(spr);
	if (!spr) {
		//log("xxxxx");
		return;
	}
	Tower[i].setAnimeIdentifier(2);
	Tower[i].SetAtkSpeedLevel(0);
	Tower[i].JudgeAttackSpeedLevel();
	//log("%f", Tower[i].attackDelay());
	Tower[i].totalHealth() = 3000;
	Tower[i].healthPower() = 3000;
	Tower[i].AttackPower() = 470;
	Tower[i].getRadium() = 150;
	//Tower[i].setAttackingSpeed(1.5);
	Tower[i].setMoveablity(false);
	Tower[i].initBloodScale();
	Tower[i].setArmor(50);
	if (!Tower[i].BloodView) {
		//log("yyyyy");
		return;
	}
	this->addChild(Tower[i].BloodView, 2);
	Tower[i].getPosition() = spr->getPosition();
}
void GameScene2::CrystalInit(int i, Sprite*& spr) {
	cryInit[i] = true;
	spr->setAnchorPoint(Vec2(0.5, 0.5));
	Crystal[i].attachToSprite(spr);
	Crystal[i].totalHealth() = 4500;
	Crystal[i].healthPower() = 4500;
	Crystal[i].AttackPower() = 630;
	Crystal[i].getRadium() = 150;
	Crystal[i].setAttackingSpeed(1.5);
	Crystal[i].setMoveablity(false);
	Crystal[i].initBloodScale();
	Crystal[i].setArmor(100);
	this->addChild(Crystal[i].BloodView, 2);
	Crystal[i].getPosition() = spr->getPosition();
}

void GameScene2::newCloseMinion(int i) {
	Sprite* minionBuf = Sprite::createWithSpriteFrameName("CloseWarriorRun1.png");
	ObjectBase minionbuf;
	minionbuf.setAnimeIdentifier(5);
	flag[i].minionInit(minionbuf,0);
	minionbuf.setArmor(10);
	minionbuf.SetAtkSpeedLevel(0);
	minionbuf.JudgeAttackSpeedLevel();
	minionbuf.attachToSprite(minionBuf);
	minionBuf->setPosition(flag[i].GetSpawn());
	minionBuf->setAnchorPoint(Vec2(0.5, 0.5));
	if (i == 1) {
		minionBuf->setFlippedX(true);
		minionBuf->setColor(Color3B::BLUE);
	}
	if (i == 0) {
		minionBuf->setColor(Color3B::RED);
	}
	minionbuf.initBloodScale();
	this->addChild(minionbuf.BloodView, 1);
	minionbuf.minionStamp = (i + 1) * 1000 + flag[i].Container().size();
	flag[i].Container().push_back(minionbuf);
	//minionAlive[*(flag[i].Container().end() - 1)] = true;
	this->addChild(minionBuf, 2);
}

void GameScene2::newDistantMinion(int i) {
	Sprite* minionBuf = Sprite::createWithSpriteFrameName("DistantWarriorRun1.png");
	ObjectBase minionbuf;
	minionbuf.setAnimeIdentifier(6);
	minionbuf.setArmor(10);
	minionbuf.SetAtkSpeedLevel(0);
	minionbuf.JudgeAttackSpeedLevel();
	flag[i].minionInit(minionbuf, 1);
	minionbuf.attachToSprite(minionBuf);
	minionBuf->setPosition(flag[i].GetSpawn());
	minionBuf->setAnchorPoint(Vec2(0.5, 0.5));
	if (i == 1) {
		minionBuf->setFlippedX(true);
		minionBuf->setColor(Color3B::BLUE);
	}
	if (i == 0) {
		minionBuf->setColor(Color3B::RED);
	}
	minionbuf.initBloodScale();
	this->addChild(minionbuf.BloodView, 1);
	minionbuf.minionStamp = (i + 1) * 1000 + flag[i].Container().size() ;
	flag[i].Container().push_back(minionbuf);
	//minionAlive[*(flag[i].Container().end() - 1)] = true;
	this->addChild(minionBuf, 2);
}

void receive() {
	while (1) {
		char buf2[100] = {};
		recv(_sock, buf2, sizeof(buf2), 0);
		if (buf2[0] == 'm') {
			int cur = 2;
			float desx, desy;
			while (buf2[cur] != '|') cur++;
			std::string pos;
			for (int i = 2; i < cur; i++) {
				pos.push_back(buf2[i]);
			}
			const char* dxs = pos.c_str();
			desx = atof(dxs);
			pos.clear();
			for (int i = cur + 1; buf2[i] != '*'; i++) {
				pos.push_back(buf2[i]);
			}
			const char* dxy = pos.c_str();
			desy = atof(dxy);

			Director::getInstance()->getScheduler()->
				performFunctionInCocosThread([desx, desy]() {eneObj->Move(Vec2(desx, desy)); });
		}
		else if (buf2[0] == 'a'){
			if (buf2[2] == 'e') {
				log("Being Attack!!!!!!");
				//log("%f %f", eneObj->AttackPower(), heroObj->AttackPower());
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					log("attack!");
					eneObj->Attack(*heroObj);
				});
			}
			if (buf2[2] == 't') {
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]() {
					//log("attack!");
					MyTower->Attack(*heroObj);
				});
			}
			if (buf2[2] == 'm') {
				std::vector<int> minionOrd;
				int a = 1, res = 0;;
				for (int i = 3; buf2[i] != '*'; i++) {
					if (isdigit(buf2[i])) minionOrd.push_back(buf2[i] - '0');
				}
				for (int i = minionOrd.size() - 1; i >= 0; i--) {
					//log("%c", minionOrd[i]);
					res += minionOrd[i] * a;
					a *= 10;
				}
				//log("%d",res);
				int Mside = (res / 1000)-1;
				int Mseq = (res % 1000);
				//log("%d", Mseq);
				//if (Mseq > mMinion->Container().size() - 1) return;
				Director::getInstance()->getScheduler()->
					performFunctionInCocosThread([Mseq](){
						eneObj->Attack(mMinion->Container()[Mseq]); 
					});
			}
		}
		else if (buf2[0] == 'b') {
			eneObj->CheckBacking() = true;
			Director::getInstance()->getScheduler()->
				performFunctionInCocosThread([]() {
				eneObj->getSprite()->stopAllActions(); });
		}
		else if (buf2[0] == 'p') {
			if (buf2[1] == 'q') {
				if (eneChoice == 1||eneChoice==2) {
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {eneObj->Ability1st(); });
				}
				else{
					//log("%d", eneChoice);
					Vec2 Qplace;
					std::string pos;
				
					int cur = 2;
					float desx, desy;
					while (buf2[cur] != '|') cur++;
					//log("%d", eneChoice);
					for (int i = 2; i < cur; i++) {
						pos.push_back(buf2[i]);
					}
					const char* dxs = pos.c_str();
					desx = atof(dxs);
					pos.clear();
					for (int i = cur + 1; buf2[i] != '*'; i++) {
						pos.push_back(buf2[i]);
					}
					const char* dxy = pos.c_str();
					desy = atof(dxy);
					log("%f %f", desx, desy);
					
					Qplace = Vec2(desx, desy);

					Vec2 Direc = Qplace - eneObj->getPosition();
					
					eneObj->QActivate = true;

					for (int i = 0; i < mMinion->Container().size(); i++) {
						Vec2 dd = mMinion->Container()[i].getPosition() - eneObj->getPosition();
						//log("%f %f", dd.x ,dd.y);
						float dy = ccpLength(ccpProject(dd, Direc));
						float dx = sqrt(ccpLength(dd)*ccpLength(dd) - dy * dy);
						//log("%f %f", dx, dy);
						if (dy <= 250 && dx <= 50) {
							eneObj->Qtarget.push_back(mMinion->Container()[i]);
						}
					}

					Vec2 dd = heroObj->getPosition() - eneObj->getPosition();
					
					//	log("%f %f", dd.x, dd.y);
					float dy = ccpLength(ccpProject(dd, Direc));
					float dx = sqrt(ccpLength(dd)*ccpLength(dd) - dy * dy);
					//	log("%f %f", dx, dy);
					if (dy <= 250 && dx <= 50) {
						eneObj->Qtarget.push_back(*heroObj);
					}
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {
						eneObj->Ability1st(); 
					});
				}
			}
			if (buf2[1] == 'w') {
				if (eneChoice == 2||eneChoice==3) {
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {
						eneObj->Ability2st();
					});
				}
				else {
					Vec2 Wplace;
					std::string pos;

					int cur = 2;
					float desx, desy;
					while (buf2[cur] != '|') cur++;
					for (int i = 2; i < cur; i++) {
						pos.push_back(buf2[i]);
					}
					const char* dxs = pos.c_str();
					desx = atof(dxs);
					pos.clear();
					for (int i = cur + 1; buf2[i] != '*'; i++) {
						pos.push_back(buf2[i]);
					}
					const char* dxy = pos.c_str();
					desy = atof(dxy);
					//log("%f %f", desx, desy);

					Wplace = Vec2(desx, desy);
					eneObj->WActivate = true;
					
					for (int i = 0; i < mMinion->Container().size(); i++) {
						if (mMinion->Container()[i].getPosition().distance(Wplace) < 100) {
							eneObj->Wtarget.push_back(mMinion->Container()[i]);
						}
					}
					if (Wplace.distance(heroObj->getPosition()) < 100) {
						eneObj->Wtarget.push_back(*heroObj);
					}
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {
						eneObj->Ability2st();
					});
				}
			}
			else if (buf2[1] == 'e') {
				if (eneChoice == 1) {

				}
				else if (eneChoice == 2) {
					eneObj->Etarget = heroObj;
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {
						eneObj->Ability3st();
					});
				}
				else if (eneChoice == 3) {
					Director::getInstance()->getScheduler()->
						performFunctionInCocosThread([]() {
						eneObj->Ability3st();
					});
				}
			}
		}
		else if (buf2[0] == 's') {
			Director::getInstance()->getScheduler()->
				performFunctionInCocosThread([]() {
				eneObj->getSprite()->stopAllActions();
			});
		}
	}
}

// on "init" you need to initialize your instance
bool GameScene2::init()
{

	std::thread recv1 = std::thread(receive);
	recv1.detach();

	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////
	
	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//Listener
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene2::onKeyPressed, this);
	//Pressed
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene2::onKeyReleased, this);
	//Pressed release
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BowmanRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BowmanAttack.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SavageRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SavageAttack.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("WizardRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("WizardAttack.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CloseWarriorRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CloseWarriorAttack.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CloseWarriorDie.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DistantWarriorRun.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("DistantWarriorAttack.plist");

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("hero");


	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	
	//log("%f %f", x, y);

	if (side == 0) {
		Hero.setAnimeIdentifier(myChoice);
		Hero.HeroInit(_player, Vec2(x, y));
		addChild(_player, 2, 200);
		addChild(Hero.BloodView, 2);
		addChild(Hero.getBullet(), 2);
		Hero.Side = 1;
	}
	if (side == 1) {
		Opponent.setAnimeIdentifier(eneChoice);
		Opponent.HeroInit(EneSpr, Vec2(x, y));
		addChild(EneSpr, 2, 200);
		addChild(Opponent.BloodView, 2);
		addChild(Opponent.getBullet(), 2);
		Opponent.Side = 0;
	}


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


	x = 877;
	y = 105;
	if (side == 1) {
		Hero.setAnimeIdentifier(myChoice);
		Hero.HeroInit(_player, Vec2(x, y));
		addChild(_player, 2, 200);
		addChild(Hero.BloodView, 2);
		addChild(Hero.getBullet(), 2);
		Hero.Side = 1;
	}
	if (side == 0) {
		Opponent.setAnimeIdentifier(eneChoice);
		Opponent.HeroInit(EneSpr, Vec2(x, y));
		addChild(EneSpr, 2, 200);
		addChild(Opponent.BloodView, 2);
		addChild(Opponent.getBullet(), 2);
		Opponent.Side = 0;
	}

    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	setViewpointCenter(_player->getPosition());

	_enemyTower->setAnchorPoint(Vec2(0.5, 0.5));
	TowerInit(0, _enemyTower);
	TowerInit(1, _myTower);

	CrystalInit(0, _myCrystal);
	CrystalInit(1, _enemyCrystal);

	scheduleUpdate();
	/*this->schedule(schedule_selector(GameScene2::timer1));
	this->schedule(schedule_selector(GameScene2::timer2));*/

	_collidable = _tileMap->getLayer("collidable");
    _collidable->setVisible(false);

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			int tileGid = _collidable->getTileGIDAt(Vec2(i, j));
			Value prop = _tileMap->getPropertiesForGID(tileGid);
			if (tileGid > 0) {
				ValueMap propValueMap = prop.asValueMap();
				std::string collision = propValueMap["Collidable"].asString();
				if (collision == "true") {
					ast.maze[i][j] = 1;
					//log("%d %d C", i, j);
				}
				else {
					ast.maze[i][j] = 0;
					//log("%d %d E", i, j);
				}
			}
		}
	}

	n_level = Hero.Level();
	sprintf(Textbuffer, "%d", n_level);
	_myLevel = Label::createWithTTF(Textbuffer, "fonts/msyh.ttc", 15);
	_myLevel->setPosition(Vec2(_player->getPosition().x-20, _player->getPosition().y+20) );
	_myLevel->setColor(Color3B::BLUE);
	addChild(_myLevel, 3);

	heroObj = &Hero;
	eneObj = &Opponent;
	MyTower = &Tower[side];
	EneTower = &Tower[!side];
	mMinion = &flag[side];
	eMinion = &flag[!side];
	return true;

}

void GameScene2::update(float delta){
	//log("%d", eneChoice);
	Hero.getPosition() = Hero.getSprite()->getPosition();
	
	if (Hero.getPosition().x<=Hero.SpawnPoint().x + 30 &&
		Hero.getPosition().x >= Hero.SpawnPoint().x - 30 &&
		Hero.getPosition().y <= Hero.SpawnPoint().y + 30 &&
		Hero.getPosition().y >= Hero.SpawnPoint().y - 30) {
		Hero.setHomerecover();
	}
	else {
		Hero.removeHomerecover();
	}//在泉水附加额外回血

	if (Opponent.getPosition().x <= Hero.SpawnPoint().x + 30 &&
		Opponent.getPosition().x >= Hero.SpawnPoint().x - 30 &&
		Opponent.getPosition().y <= Hero.SpawnPoint().y + 30 &&
		Opponent.getPosition().y >= Hero.SpawnPoint().y - 30) {
		eneHome += delta; 
		if (eneHome >= 1) {
			eneHome = 0;
			Opponent.BeAttack(1000);
		}
	}
	else {
		eneHome = 1;
	}

	Hero.ExpAndMoneyIncrease(delta);//金币经验的自然增长
	Hero.HealthRebound(delta);//自然回血
	Hero.MagicRebound(delta);//自然回蓝

	Hero.BloodView->setCurrentProgress(Hero.healthPower());
	Hero.BloodView->setPosition(Vec2(Hero.getPosition().x, Hero.getPosition().y + 15));
	
	Opponent.getPosition() = Opponent.getSprite()->getPosition();

	if (Opponent.getPosition().x <= Opponent.SpawnPoint().x + 30 &&
		Opponent.getPosition().x >= Opponent.SpawnPoint().x - 30 &&
		Opponent.getPosition().y <= Opponent.SpawnPoint().y + 30 &&
		Opponent.getPosition().y >= Opponent.SpawnPoint().y - 30) {
		Opponent.setHomerecover();
	}
	else {
		Opponent.removeHomerecover();
	}//在泉水附加额外回血

	if (Hero.getPosition().x <= Opponent.SpawnPoint().x + 30 &&
		Hero.getPosition().x >= Opponent.SpawnPoint().x - 30 &&
		Hero.getPosition().y <= Opponent.SpawnPoint().y + 30 &&
		Hero.getPosition().y >= Opponent.SpawnPoint().y - 30) {
		myHome += delta;
		if (myHome >= 1) {
			myHome = 0;
			Hero.BeAttack(1000);
		}
	}
	else {
		myHome = 1;
	}

	Opponent.ExpAndMoneyIncrease(delta);//金币经验的自然增长
	Opponent.HealthRebound(delta);//自然回血
	Opponent.MagicRebound(delta);//自然回蓝

	Opponent.BloodView->setCurrentProgress(Opponent.healthPower());
	Opponent.BloodView->setPosition(Vec2(Opponent.getPosition().x, Opponent.getPosition().y + 15));

	if (Hero.QIsUsed()) {
		Hero.Qjudge(delta);
	}
	if (Hero.WIsUsed()) {
		Hero.Wjudge(delta);
	}
	if (Hero.EIsUsed()) {
		Hero.Ejudge(delta);
	}//判断三个技能的冷却时间并进行冷却的计时

	if (Opponent.QIsUsed()) {
		Opponent.Qjudge(delta);
	}
	if (Opponent.WIsUsed()) {
		Opponent.Wjudge(delta);
	}
	if (Opponent.EIsUsed()) {
		Opponent.Ejudge(delta);
	}//判断三个技能的冷却时间并进行冷却的计时

	Tower[0].BloodView->setCurrentProgress(Tower[0].healthPower());
	Tower[1].BloodView->setCurrentProgress(Tower[1].healthPower());
	
	if(cryInit[0]) Crystal[0].BloodView->setCurrentProgress(Crystal[0].healthPower());
	if(cryInit[1]) Crystal[1].BloodView->setCurrentProgress(Crystal[1].healthPower());
	

	if (Tower[0].healthPower() <= 0 && Crystal[0].healthPower() <= 0) Director::getInstance()->replaceScene(HelloWorld::createScene());

	if (_player->getPosition() == prelocation) {
		//_player->stopAllActions();
		if (pathFound.size() > 0) {
			if (Hero.getPosition() == Vec2(31 * pathFound.front()->x + 16,
				1024 - (31 * pathFound.front()->y + 16)-32)) {
				playMove();
			}
		}
	}
	else {
		Hero.Interrupt();
		backSpawn = 0;
	}
	prelocation = _player->getPosition();

	if (Hero.CheckBacking()) {
		Hero.JudgeBack(backSpawn, delta);
	}

	if(eprelocation!=Opponent.getPosition()){
		Opponent.Interrupt();
		ebackSpawn = 0;
	}
	eprelocation = EneSpr->getPosition();

	if (Opponent.CheckBacking()) {
		Opponent.JudgeBack(ebackSpawn, delta);
	}


	for (int i = 0; i < flag[0].Container().size(); i++) {
		if (flag[0].Container()[i].Death()) continue;

		if (flag[0].Container()[i].isAttacking()&& flag[0].Container()[i].healthPower()>0) {
			flag[0].Judge(i, delta);
		}
		if (flag[0].Container()[i].healthPower() > 0) {
			flag[0].Container()[i].getPosition() = flag[0].Container()[i].getSprite()->getPosition();
			flag[0].Container()[i].BloodView->setPosition(Vec2(flag[0].Container()[i]
				.getPosition().x, flag[0].Container()[i].getPosition().y + 15));
			flag[0].Container()[i].BloodView->setCurrentProgress(flag[0].Container()[i].healthPower());
		}

		if (flag[0].Container()[i].getPosition().distance(Tower[0].getPosition()) < Tower->getRadium()
			&& flag[0].Container()[i].healthPower() > 0) {
			Tower[0].Attack(flag[0].Container()[i]);
		}
	}

	for (int i = 0; i < flag[1].Container().size() ; i++) {
		if (flag[1].Container()[i].Death()) continue;

		if (flag[1].Container()[i].isAttacking()) {
			flag[1].Judge(i, delta);
		}
		
		flag[1].Container()[i].getPosition() = flag[1].Container()[i].getSprite()->getPosition();
		flag[1].Container()[i].BloodView->setPosition(Vec2(flag[1].Container()[i]
			.getPosition().x, flag[1].Container()[i].getPosition().y + 15));
		flag[1].Container()[i].BloodView->setCurrentProgress(flag[1].Container()[i].healthPower());
	
		if(flag[1].Container()[i].getPosition().distance(Tower[1].getPosition()) < Tower->getRadium() ) {
			Tower[1].Attack(flag[1].Container()[i]);
		}
	}

	minionCnt += delta;
	if (minionCnt > 0.4&&reverse) {
		for (int i = 0; i < flag[0].Container().size(); i++) {
			if (flag[0].Container()[i].Death()) continue;
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
			if (Tower[0].healthPower() > 0) {
				float dis = flag[0].Container()[i].getPosition().distance(Tower[0].getPosition());
				if (dis < Tower[0].getRadium()) {
					flag[0].getPlan(i) = Tower[0].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &Tower[0];
						tarck = true;
					}
					ck = true;
				}
			}
			else {
				float dis = flag[0].Container()[i].getPosition().distance(Crystal[0].getPosition());
				if (dis < Crystal[0].getRadium()) {
					flag[0].getPlan(i) = Crystal[0].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &Crystal[0];
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
				flag[0].getPlan(i) = flag[0].Container()[i].getPosition();
				reverse = !reverse;
			}
		}

		for (int i = 0; i < flag[1].Container().size(); i++) {
			if (flag[1].Container()[i].Death()) continue;
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
			if (Tower[1].healthPower() > 0) {
				float dis = flag[1].Container()[i].getPosition().distance(Tower[1].getPosition());
				if (dis < Tower[1].getRadium()) {
					flag[1].getPlan(i) = Tower[1].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &Tower[1];
						tarck = true;
					}
					ck = true;
				}
			}
			else {
				float dis = flag[1].Container()[i].getPosition().distance(Crystal[1].getPosition());
				if (dis < Crystal[1].getRadium()) {
					flag[1].getPlan(i) = Crystal[1].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &Crystal[1];
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
				flag[1].getPlan(i) = flag[1].Container()[i].getPosition();
			}
		}

		flag[0].MoveToTarget();
		flag[1].MoveToTarget();

		minionCnt = 0;
	}

	if (minionCnt > 0.4&&!reverse) {
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
			if (Tower[1].healthPower() > 0) {
				float dis = flag[1].Container()[i].getPosition().distance(Tower[1].getPosition());
				if (dis < Tower[1].getRadium()) {
					flag[1].getPlan(i) = Tower[1].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &Tower[1];
						tarck = true;
					}
					ck = true;
				}
			}
			else {
				float dis = flag[1].Container()[i].getPosition().distance(Crystal[1].getPosition());
				if (dis < Crystal[1].getRadium()) {
					flag[1].getPlan(i) = Crystal[1].getPosition();
					if (dis < flag[1].Container()[i].getRadium()) {
						target = &Crystal[1];
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
				flag[1].getPlan(i) = flag[1].Container()[i].getPosition();
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
			if (Tower[0].healthPower() > 0) {
				float dis = flag[0].Container()[i].getPosition().distance(Tower[0].getPosition());
				if (dis < Tower[0].getRadium()) {
					flag[0].getPlan(i) = Tower[0].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &Tower[0];
						tarck = true;
					}
					ck = true;
				}
			}
			else {
				float dis = flag[0].Container()[i].getPosition().distance(Crystal[0].getPosition());
				if (dis < Crystal[0].getRadium()) {
					flag[0].getPlan(i) = Crystal[0].getPosition();
					if (dis < flag[0].Container()[i].getRadium()) {
						target = &Crystal[0];
						tarck = true;
					}
					ck = true;
				}
			}
			if (!ck) {
				flag[0].getPlan(i) = flag[0].GetDes();
			}
			if (tarck) {
				flag[0].getPlan(i) = flag[0].Container()[i].getPosition();
				flag[0].Container()[i].Attack(*target);
			}
		}

		flag[0].MoveToTarget();
		flag[1].MoveToTarget();

		minionCnt = 0;
		reverse = !reverse;
	}
	
	//生成一波小兵
	//因为每个小兵之间生成有一定的时间差，所以简单地采用了五次函数调用
	minioncount1 += delta;
	minioncount2 += delta;
	minioncount3 += delta;
	minioncount4 += delta;
	minioncount5 += delta;
	if (minioncount5 > minionborn) {
		minioncount5 = 0;
		newCloseMinion(0);
		newCloseMinion(1);
	}
	if (minioncount4 > minionborn) {
		minioncount4 = 0;
		newCloseMinion(0);
		newCloseMinion(1);
	}
	if (minioncount3 > minionborn) {
		minioncount3 = 0;
		newCloseMinion(0);
		newCloseMinion(1);
	}
	if (minioncount2 > minionborn) {
		minioncount2 = 0;
		newDistantMinion(0);
		newDistantMinion(1);
	}
	if (minioncount1 > minionborn) {
		minioncount1 = 0;
		newDistantMinion(0);
		newDistantMinion(1);
	}
	//log("side:%d", side);
	if (Hero.getPosition().distance(Tower[side].getPosition()) < Tower[side].getRadium()) {
		Tower[side].Attack(Hero);
	}
	if (Opponent.getPosition().distance(Tower[!side].getPosition()) < Tower[!side].getRadium()) {
		Tower[!side].Attack(Opponent);
	}

	if (Hero.getPosition().distance(Crystal[!side].getPosition()) < Crystal[!side].getRadium()) {
		Crystal[!side].Attack(Hero);
	}
	if (Opponent.getPosition().distance(Crystal[side].getPosition()) < Crystal[side].getRadium()) {
		Crystal[side].Attack(Opponent);
	}

	if (Hero.isAttacking()) {
		m_atktime += delta;
		Hero.JudgeAttack(m_atktime);
	}

	if (Opponent.isAttacking()) {
		e_atktime += delta;
		Opponent.JudgeAttack(e_atktime);
	}

	if (Tower[0].isAttacking()) {
		mt_atktime += delta;
		Tower[0].JudgeAttack(mt_atktime);
	}

	if (Tower[1].isAttacking()) {
		et_atktime += delta;
		Tower[1].JudgeAttack(et_atktime);
	}

	if (Crystal[0].isAttacking()) {
		mc_atktime += delta;
		Crystal[0].JudgeAttack(mc_atktime);
	}

	if (Crystal[1].isAttacking()) {
		ec_atktime += delta;
		Crystal[1].JudgeAttack(ec_atktime);
	}

	if (Hero.Death()) {
		deathtime += delta;
		if (deathtime > Hero.DeadTime) {
			Hero.revive();
			deathtime = 0;
		}
	}

	if (Opponent.Death()) {
		edeathtime += delta;
		if (edeathtime > Opponent.DeadTime) {
			Opponent.revive();
			edeathtime = 0;
		}
	}

	setViewpointCenter(_player->getPosition());
	_myLevel->setPosition(Vec2(_player->getPosition().x-20, _player->getPosition().y+20));
	if (n_level != Hero.Level())
	{
		n_level = Hero.Level();
		sprintf(Textbuffer, "%d", n_level);
	}
}

bool GameScene2::onTouchBegan(Touch* touch, Event* event)
{
	Hero.getSprite()->stopAllActions();

	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());

	Hero.getSprite()->stopAllActions();
    //log("onTouchBegan");
	//log("%f %f", locationInNode.x, locationInNode.y);
	int eneSide = !side;
	log("%d", eneSide);
	if (Hero.QBoundJudge == true) {
		//Vec2 Direc = touch->getLocation() - Hero.getPosition();
		//log("%f", locationInNode.distance(Hero.getPosition()));
		if (locationInNode.distance(Hero.getPosition())<=200) {
			//log("Judge activate");//correct
			Vec2 Direc = locationInNode - Hero.getPosition();
			Hero.QActivate = true;
			for (int i = 0; i < flag[eneSide].Container().size(); i++) {
				Vec2 dd = flag[eneSide].Container()[i].getPosition() - Hero.getPosition();
				//log("%f %f", dd.x ,dd.y);
				if (dd.x*Direc.x < 0 || dd.y*Direc.y < 0) continue;
				float dy = ccpLength(ccpProject(dd, Direc));
				float dx = sqrt(ccpLength(dd)*ccpLength(dd) - dy * dy);
				//log("%f %f", dx, dy);
				if (dy<=250&&dx<=50) {
					Hero.Qtarget.push_back(flag[eneSide].Container()[i]);
				}
			}
			Vec2 dd = Opponent.getPosition() - Hero.getPosition();
		//	log("%f %f", dd.x, dd.y);
			float dy = ccpLength(ccpProject(dd, Direc));
			float dx = sqrt(ccpLength(dd)*ccpLength(dd) - dy * dy);
		//	log("%f %f", dx, dy);
			if (dy<=250&&dx<=50) {
				Hero.Qtarget.push_back(Opponent);
			}

			std::string Qactivation;
			Qactivation.push_back('p');
			Qactivation.push_back('q');
			Qactivation += std::to_string(locationInNode.x);
			Qactivation.push_back('|');
			Qactivation += std::to_string(locationInNode.y);
			Qactivation.push_back('*');
			const char* QActorder = Qactivation.c_str();
			send(_sock, QActorder, 100, 0);

			Hero.Ability1st();
			return true;
		}
		else {
			Hero.QBoundJudge = false;
		}
	}

//	log("%d", Hero.EBoundJudge);
	if (Hero.EBoundJudge == true) {
	//	log("(%f %f) (%f,%f) %f", locationInNode.x, locationInNode.y,
	//		Opponent.getPosition().x, Opponent.getPosition().y, 
	//		locationInNode.distance(Opponent.getPosition()));
		if (locationInNode.distance(Opponent.getPosition()) <= 20&&
			locationInNode.distance(Hero.getPosition())<200) {
			Hero.EActivate = true;
			Hero.Etarget = &Opponent;
			Hero.Ability3st();
			return true;
		}
		else {
		//	log("E bound judge false");
			Hero.EBoundJudge = false;
		}
	}

	if (Hero.WBoundJudge == true) {
		if (Hero.HeroIdentifier == 1) {
			if (touch->getLocation().distance(Hero.getPosition()) < 250) {
				Hero.WActivate = true;
				for (int i = 0; i < flag[eneSide].Container().size(); i++) {
					if (flag[eneSide].Container()[i].getPosition().distance(touch->getLocation()) < 100) {
						Hero.Wtarget.push_back(flag[eneSide].Container()[i]);
					}
				}
				if (touch->getLocation().distance(Opponent.getPosition()) < 100) {
					Hero.Wtarget.push_back(Opponent);
				}
				Hero.Ability2st();
				return true;
			}
			else {
				Hero.WBoundJudge = false;
			}
		}
	}

	float TargetMinimum = 100000;
	ObjectBase* MouseTar = nullptr;
	bool mouseTarCheck = false;
	for (int i = 0; i < flag[eneSide].Container().size(); i++) {
		if (!Hero.InRange(flag[eneSide].Container()[i].getPosition())) continue;
		float disMouse = locationInNode.distance(flag[eneSide].Container()[i].getPosition());
		if (disMouse < TargetMinimum&&disMouse < 30) {
			TargetMinimum = disMouse;
			MouseTar = &(flag[eneSide].Container()[i]);
		}
	}

	if (Tower[0].healthPower() > 0) {
		float disMouseTower = locationInNode.distance(Tower[side].getPosition());
		//log("%f", disMouseTower);
		if (Hero.InRange(Tower[side].getPosition()) && disMouseTower < TargetMinimum&&disMouseTower < 20) {
			MouseTar = &Tower[side];
		}
	}
	else {
		float disMouseTower = locationInNode.distance(Crystal[side].getPosition());
		if (disMouseTower < TargetMinimum&&disMouseTower < 20) {
			MouseTar = &Crystal[side];
		}
	}
	if (Opponent.healthPower() > 0) {
		float disMouseEne = locationInNode.distance(Opponent.getPosition());
		//log("%f", disMouseTower);
		if (Hero.InRange(Opponent.getPosition()) && disMouseEne < TargetMinimum&&disMouseEne < 20) {
			MouseTar = &Opponent;
		}
	}
	if (MouseTar != nullptr) {
		Hero.getSprite()->stopAllActions();
		Hero.Attack(*MouseTar);
		return true;
	}

	Vec2 faceDirection = touch->getLocation() - Hero.getPosition();
	if (faceDirection.x < 0 && !isRight) {
		isRight = true;
		Hero.getSprite()->setFlippedX(true);
	}
	else if (faceDirection.x > 0 && isRight) {
		isRight = false;
		Hero.getSprite()->setFlippedX(false);
	}
	Vec2 myCoord = this->tileCoordFromPosition(Hero.getPosition());

	Vec2 tileCoord = this->tileCoordFromPosition(locationInNode);
	
	Vec2 vectorPoint = (locationInNode - Hero.getPosition())/64;
	Vec2 iter = Hero.getPosition();
	bool routeColli = false;
	while (abs(iter.x -locationInNode.x)>0.1) {
		iter += vectorPoint;
		//log("%f %f", iter.x, iter.y);
		Vec2 tileIter = this->tileCoordFromPosition(iter);
		//log("%d %d", int(tileIter.x), int(tileIter.y));
		//log("%d", ast.maze[int(tileIter.x)][int(tileIter.y)]);
		if (ast.maze[int(tileIter.x)][int(tileIter.y)] == 1) {
			routeColli = true;
		}
	}

	int lx = (int)tileCoord.x;
	int ly = (int)tileCoord.y;
	//log("(%d %d) (%d %d)", lx, ly, int(myCoord.x), int(myCoord.y));
	PointCk start(int(myCoord.x), int(myCoord.y));
	PointCk end(lx, ly);
	
	while (!pathFound.empty())
	{
		pathFound.pop_back();
	}
	if (routeColli) {
		pathFound = ast.GetPath(start, end, true);
	}
	//playMove();

	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("wall %d %d",lx,ly);
			return false;
		}
	}
	else {
		if(pathFound.size()!=0) playMove();
		if(!routeColli) {
			Hero.Move(locationInNode);
		}
		//log("%f %f", locationInNode.x, locationInNode.y);
	}


	return true;
}

void GameScene2::onTouchMoved(Touch *touch, Event *event)
{
	//log("onTouchMoved");
}

void GameScene2::onTouchEnded(Touch *touch, Event *event)
{
	//log("onTouchEnded");
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


void GameScene2::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_B) {
		Hero.CheckBacking() = true;
		Hero.getSprite()->stopAllActions();
		char order[100] = {};
		order[0] = 'b';
		order[1] = '*';
		send(_sock, order, 100, 0);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_M) {
		Hero.setMoney(100000);
	}
	if (keycode == EventKeyboard::KeyCode::KEY_Q) {
		//log("Q is pressed!%d should be activate",Hero.HeroIdentifier);
		if (Hero.QIsUsed()) return;
		if (Hero.HeroIdentifier == 1 || Hero.HeroIdentifier == 2) {
			Hero.Ability1st();
			char Qorder[100] = {};
			Qorder[0] = 'p';
			Qorder[1] = 'q';
			Qorder[2] = '*';
			send(_sock, Qorder, 100, 0);
		}
		if (Hero.HeroIdentifier == 3) Hero.QBoundJudge = true;
	}
	if (keycode == EventKeyboard::KeyCode::KEY_W) {
		if (Hero.WIsUsed()) return;
		if (Hero.HeroIdentifier == 1) Hero.WBoundJudge = true;
		if (Hero.HeroIdentifier == 2) {
			Hero.Ability2st();
			char Worder[100] = {};
			Worder[0] = 'p';
			Worder[1] = 'w';
			Worder[2] = '*';
			send(_sock, Worder, 100, 0);
		}
		if (Hero.HeroIdentifier == 3) {
			if (Opponent.getPosition().distance(Hero.getPosition()) <= 100) {
				Hero.Wtarget.push_back(Opponent);
				Hero.Ability2st(); 
				char Worder[100] = {};
				Worder[0] = 'p';
				Worder[1] = 'w';
				Worder[2] = '*';
				send(_sock, Worder, 100, 0);
			}
		}
	}
	if (keycode == EventKeyboard::KeyCode::KEY_E) {
		if (Hero.EIsUsed()) return;
		if (Hero.HeroIdentifier == 1) {

		}
		if (Hero.HeroIdentifier == 2) {
			if(Opponent.getPosition().distance(Hero.getPosition())<=100){
				Hero.Etarget = &Opponent;
				Hero.Ability3st();
				char Eorder[100] = {};
				Eorder[0] = 'p';
				Eorder[1] = 'e';
				Eorder[2] = '*';
				send(_sock, Eorder, 100, 0);
			}
		}
		if (Hero.HeroIdentifier == 3) {
			char Eorder[100] = {};
			Eorder[0] = 'p';
			Eorder[1] = 'e';
			Eorder[2] = '*';
			send(_sock, Eorder, 100, 0);
			Hero.Ability3st();
		}
	}
	if (keycode == EventKeyboard::KeyCode::KEY_S) {
		char stopActionOrder[100] = {};
		stopActionOrder[0] = 's';
		stopActionOrder[1] = '*';
		send(_sock, stopActionOrder, 100, 0);
		Hero.getSprite()->stopAllActions();
	}
}

void GameScene2::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {

}


Vec2 GameScene2::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x,y);
}

void GameScene2::setViewpointCenter(Vec2 position)
{
	//log("setViewpointCenter");

	//log("position (%f ,%f) ",position.x,position.y);

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
	//log("目标位置 (%f ,%f) ",pointB.x,pointB.y);

    //地图移动偏移量
    Vec2 offset =pointA - pointB;
   // log("offset (%f ,%f) ",offset.x, offset.y);
    this->setPosition(offset);

}

void GameScene2::playMove() {
	if (pathFound.size() == 1) {
		Vec2 dest = Vec2(31 * pathFound.front()->x + 16,
			1024 - (31 * (pathFound.front()->y) + 16) - 32);
		Hero.getBullet()->setPosition(dest);
		Hero.Move(dest);
		return;
	}
	if (pathFound.size() != 0) {
		//log("%d %d", pathFound.front()->x, pathFound.front()->y);
		pathFound.pop_front();
		Vec2 dest = Vec2(31 * pathFound.front()->x + 16,
			1024 - (31 * (pathFound.front()->y) + 16) - 32);
		Hero.getBullet()->setPosition(dest);
		Hero.Move(dest);
	}
	/*Hero.getSprite()->runAction(Sequence::create(MoveTo::create(0.02, dest),
		CCCallFunc::create(this,SEL_CallFunc(&GameScene2::playMove)),NULL));*/
}
