/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Help.h"
#include "Avene.h"
#include "Setting.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	CocosDenshion::SimpleAudioEngine::sharedEngine()
		->playBackgroundMusic("Ariana Grande - 7 rings (Explicit) [mqms2].mp3", true);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Summer.mp3", true);


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	auto startItem = MenuItemImage::create("StartButton.jpg",
											"StartButton2.jpg",
										   CC_CALLBACK_1(HelloWorld::menuStartCallback,this));
	startItem->setPosition(500, 105);

	auto settingItem = MenuItemImage::create("settings.jpg",
		"settings.jpg",
		CC_CALLBACK_1(HelloWorld::settingCallback, this));

	auto helpItem = MenuItemImage::create("Help.png",
											"Help.png",
											CC_CALLBACK_1(HelloWorld::helpCallback,this));
	helpItem->setPosition(visibleSize.width-helpItem->getContentSize().width,
		                  visibleSize.height-helpItem->getContentSize().height);
	
	settingItem->setPosition( helpItem->getContentSize().width,
		visibleSize.height - helpItem->getContentSize().height);


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));


    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width- closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }


    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem,helpItem,closeItem,settingItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

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
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 5);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Entrance.png");
    if (sprite == nullptr)
    {
        problemLoading("'Entrance.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuStartCallback(cocos2d::Ref* pSender) {
	auto startCreate = Avene::createScene();
	auto startCreateChange = TransitionFadeTR::create(1.0f, startCreate);
	Director::getInstance()->pushScene(startCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav",false);
}

void HelloWorld::helpCallback(cocos2d::Ref* pSender) {
	auto helpCreate = helpScene::createScene();
	auto helpCreateChange = TransitionFadeTR::create(1.0f, helpCreate);
	Director::getInstance()->pushScene(helpCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void HelloWorld::settingCallback(cocos2d::Ref* pSender) {
	auto settingCreate = SettingScene::createScene();
	auto settingCreateChange = TransitionFadeTR::create(1.0f, settingCreate);
	Director::getInstance()->pushScene(settingCreateChange);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effectmusic1.wav", false);
}

void HelloWorld::musicCallback(cocos2d::Ref* pSender) {
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Summer.mp3", true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Taylor Swift _ Brendon Urie - ME! (feat. Brendon Urie of Panic! At The Disco).mp3", true);
}
