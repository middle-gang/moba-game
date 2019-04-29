#include "menuScene1st.h"
#include "Setting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool MusicPlayVal = true;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	MenuScene1st::init();

	auto MusicButton = MenuItemFont::create("MusicPlay",
			CC_CALLBACK_1(SettingScene::MusicCallback,this));
	MusicButton->setColor(Color3B::YELLOW);
	MusicButton->setFontNameObj("Ink Free");
	MusicButton->setFontSizeObj(30);
	MusicButton->setPosition(400, 335);

	auto MusicUpButton = MenuItemFont::create("Up",
		CC_CALLBACK_1(SettingScene::MusicUpCallback, this));
	MusicUpButton->setColor(Color3B::YELLOW);
	MusicUpButton->setFontNameObj("Ink Free");
	MusicUpButton->setFontSizeObj(30);
	MusicUpButton->setPosition(550, 335);

	auto MusicDownButton = MenuItemFont::create("Down",
		CC_CALLBACK_1(SettingScene::MusicDownCallback, this));
	MusicDownButton->setColor(Color3B::YELLOW);
	MusicDownButton->setFontNameObj("Ink Free");
	MusicDownButton->setFontSizeObj(30);
	MusicDownButton->setPosition(700, 335);

	auto mu = Menu::create(MusicButton,MusicUpButton,MusicDownButton, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return true;
}

void SettingScene::MusicCallback(cocos2d::Ref* pSender) {
	if (MusicPlayVal) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		MusicPlayVal = false;
	}
	else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		MusicPlayVal = true;
	}
}

void SettingScene::MusicUpCallback(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->
		setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1);
}

void SettingScene::MusicDownCallback(cocos2d::Ref* pSender) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->
		setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 100);
}