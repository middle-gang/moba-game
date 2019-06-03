#include "DisplayLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* DisplayLayer::createScene()
{
	return DisplayLayer::create();
}

// on "init" you need to initialize your instance
bool DisplayLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	////ÓÎÏ·Ê±¼ä
	time_min = 0;
	time_sec = 0;
	time = 0;
	number = 0;

	sprintf(m_textContain, "%d", time_min);
	m_pTime_minText = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 23);
	m_pTime_minText->setPosition(80, 405);
	addChild(m_pTime_minText, 3);

	sprintf(m_textContain, "%d", time_sec);
	m_pTime_secText = Label::createWithTTF(m_textContain, "fonts/msyh.ttc", 23);
	m_pTime_secText->setPosition(110, 405);
	addChild(m_pTime_secText, 3);


	return true;
}
void DisplayLayer::update(float delta)
{
	time += delta;
	time_sec = int(time) % 60;
	if (time_sec >= 59)
	{
		number++;
		if (number >= 59)
		{
			time_min++;
			number = 0;
		}
	}

	sprintf(m_textContain, "%d", time_sec);
	m_pTime_secText->setString(m_textContain);

	sprintf(m_textContain, "%d", time_min);
	m_pTime_minText->setString(m_textContain);
}


