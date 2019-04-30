#include "GameScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "atltypes.h"

USING_NS_CC;

Vec2 direc[8] = {
	Vec2(1,0),Vec2(-1,0),Vec2(0,1),Vec2(0,-1),
	Vec2(1,1),Vec2(1,-1),Vec2(-1,1),Vec2(-1,-1)
};

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// 添加屏幕点击事件监听
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();
	//如果不加入此句消息依旧会向下传递  
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = std::bind(&GameScene::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
	myListener->onTouchMoved = std::bind(&GameScene::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
	myListener->onTouchEnded = std::bind(&GameScene::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
	dispatcher->addEventListenerWithSceneGraphPriority(myListener, this);

	auto* dsptchr = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//键盘被按下时响应
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	//键盘按键被弹回时响应
	dsptchr->addEventListenerWithSceneGraphPriority(keyListener, this);

	MySprite = Sprite::create("qian.png");
	MySprite->setPosition(500, 235);
	MySprite->setScale(0.5);
	this->addChild(MySprite, 3);

	// add a "close" icon to exit the progress. it's an autorelease object

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	auto backItem = MenuItemImage::create("back.jpg",
		"back.jpg",
		CC_CALLBACK_1(GameScene::backCallback, this));
	backItem->setPosition(1000 - backItem->getContentSize().width,
		473 - backItem->getContentSize().height);

	auto homeItem = MenuItemImage::create(
		"home.jpg",
		"home.jpg",
		CC_CALLBACK_1(GameScene::homeCallback, this));
	homeItem->setPosition(homeItem->getContentSize().width, 473 - homeItem->getContentSize().height);

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, homeItem, backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("TJU-Middle-Gang", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	return true;
}


void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	MySprite->stopAllActions();
	des = pTouch->getLocation();
	now = MySprite->getPosition();
	Vec2 dir = des - now, bestDir;
	float bestangl = 0;
	for (int i = 0; i < 8; i++) {
		float ang = dir.getAngle(direc[i]);
		if (ang < bestangl) {
			bestangl = ang;
			bestDir = direc[i];
		}
	}
	if (bestDir == Vec2(1, 0)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zuo.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(-1, 0)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("you.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(0, 1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("qian.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(0, -1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("hou.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(1, 1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zuoxia.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(1, -1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("zuoshang.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(-1, 1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("youxia.png");
		MySprite->setTexture(texture);
	}
	if (bestDir == Vec2(-1, -1)) {
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("youshang.png");
		MySprite->setTexture(texture);
	}
	float time = ccpDistance(des, now) / Sspeed;
	//float time = 3;
	MySprite->runAction(MoveTo::create(time, des));
	return true;
}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
	if (keycode == EventKeyboard::KeyCode::KEY_TAB) {
		MenuTab->runAction(ToggleVisibility::create());
	}
	if (keycode == EventKeyboard::KeyCode::KEY_SHIFT) {
		Sspeed = 500;
	}
	if (keycode == EventKeyboard::KeyCode::KEY_Q) {
		charQ = Sprite::create("HelloKitty.jpg");
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		CCLOG("%d %d", MousePoint.x, MousePoint.y);
		charQ->setPosition(MousePoint.x, 1080 - MousePoint.y);
		this->addChild(charQ, 3);
		//chrQ->runAction(MoveTo::create(1, Vec2(now.x + 500, now.y)));
		//this->removeChild(chrQ);
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event * event) {
	if (keycode == EventKeyboard::KeyCode::KEY_TAB) {
		MenuTab->runAction(ToggleVisibility::create());
	}
	if (keycode == EventKeyboard::KeyCode::KEY_SHIFT) {
		Sspeed = 200;
	}
	if (keycode == EventKeyboard::KeyCode::KEY_Q) {
	}
}