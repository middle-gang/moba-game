#include "BottemLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BottemLayer::createScene()
{
	return BottemLayer::create();
}

// on "init" you need to initialize your instance
bool BottemLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//通用技能
	pAttackMii = MenuItemImage::create("photo/attack.png", "photo/attack-1.png",
		CC_CALLBACK_1(BottemLayer::attack, this));
	pAttackMii->setPosition(40, 90);

	pRecoverMii = MenuItemImage::create("photo/recover.png", "photo/recover1.png", "photo/recover1.png",
		CC_CALLBACK_1(BottemLayer::recover, this));
	pRecoverMii->setPosition(145, 25);

	pCureMii = MenuItemImage::create("photo/cure.jpg", "photo/cure1.png", "photo/cure1.png",
		CC_CALLBACK_1(BottemLayer::cure, this));
	pCureMii->setPosition(195, 25);

	pSkill1Mii = MenuItemImage::create("photo/Arthur/Arthur1.png", "photo/Arthur/Arthur1-2.png", "photo/Arthur/Arthur1-2.png",
		CC_CALLBACK_1(BottemLayer::Skill1, this));
	pSkill1Mii->setPosition(70, 150);

	pSkill2Mii = MenuItemImage::create("photo/Arthur/Arthur2.png", "photo/Arthur/Arthur2-2.png", "photo/Arthur/Arthur2-2.png",
		CC_CALLBACK_1(BottemLayer::Skill2, this));
	pSkill2Mii->setPosition(120, 90);

	pSkill3Mii = MenuItemImage::create("photo/Arthur/Arthur3.png", "photo/Arthur/Arthur3-2.png", "photo/Arthur/Arthur3-2.png",
		CC_CALLBACK_1(BottemLayer::Skill3, this));
	pSkill3Mii->setPosition(70, 30);

	


	m_pSkillMenu = Menu::create(pSkill1Mii, pSkill2Mii, pSkill3Mii, pAttackMii, pRecoverMii, pCureMii, NULL);
	m_pSkillMenu->setPosition(Vec2::ZERO);
	addChild(m_pSkillMenu, 1);
	



	return true;
}

void BottemLayer::update(float delta)
{
}

void BottemLayer::attack(cocos2d::Ref* pSender)
{
	//pAttackMii->setEnabled(false);
}

void BottemLayer::recover(cocos2d::Ref* pSender)
{
	//pRecoverMii->setEnabled(false);
}

void BottemLayer::cure(cocos2d::Ref* pSender)
{
	//pCureMii->setEnabled(false);
}

void BottemLayer::Skill1(cocos2d::Ref* pSender)
{
	//pSkill1Mii->setEnabled(false);

}

void BottemLayer::Skill2(cocos2d::Ref* pSender)
{
	//pSkill2Mii->setEnabled(false);
}

void BottemLayer::Skill3(cocos2d::Ref* pSender)
{
	//pSkill3Mii->setEnabled(false);
}



