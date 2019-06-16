#include "ChooseCharacter.h"
#include"GameScene0.h"
#include"Object.h"
#include "SimpleAudioEngine.h"
#include"GlobalVal.h"
#include"HelloWorldScene.h"
#include"Avene.h"
USING_NS_CC;

void connectToServer()
{
	// 启动Windows socket 2.x环境

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	// 建立一个socket

	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("创建套接字错误...\n");
	}
	// 连接服务器 connect

	sockaddr_in _sin = {};

	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(9527);
	_sin.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");

	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));

	if (SOCKET_ERROR == ret) {
		printf("连接服务器错误...\n");
	}
	else {
		printf("连接Socket成功...\n");
	}

}

Scene* ChooseCharacter::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseCharacter::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharacter::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	m_IsChangeScene = false;

	ChooseHero = 2;

	m_pBowmanIntro = Sprite::create("photo/character/intro1.png");
	m_pBowmanIntro->setPosition(520, 200);
	addChild(m_pBowmanIntro, 1);
	m_pBowmanIntro->setVisible(false);
	
    m_pSavageIntro = Sprite::create("photo/character/intro2.png");
	m_pSavageIntro->setPosition(520, 200);
	addChild(m_pSavageIntro, 1);

	m_pWizardIntro = Sprite::create("photo/character/intro3.png");
	m_pWizardIntro->setPosition(520, 200);
	addChild(m_pWizardIntro, 1);
	m_pWizardIntro->setVisible(false);

	m_pBowmanMII=MenuItemImage::create(
		"photo/character/Bowman0.png",
		"photo/character/Bowman.png",
		"photo/character/Bowman.png",
		CC_CALLBACK_1(ChooseCharacter::BowmanIntro, this));

	m_pSavageMII = MenuItemImage::create(
		"photo/character/Savage0.png",
		"photo/character/Savage.png",
		"photo/character/Savage.png",
		CC_CALLBACK_1(ChooseCharacter::SavageIntro, this));
	m_pSavageMII->setEnabled(false);

	m_pWizardMII = MenuItemImage::create(
		"photo/character/Wizard0.png",
		"photo/character/Wizard.png",
		"photo/character/Wizard.png",
		CC_CALLBACK_1(ChooseCharacter::WizardIntro, this));

	MenuItemImage* ChooseMII = MenuItemImage::create(
		"photo/character/choose0.png",
		"photo/character/choose.png",
		CC_CALLBACK_1(ChooseCharacter::enterGameCallBack, this));

	MenuItemImage* ReturnMII = MenuItemImage::create(
		"photo/character/return0.png",
		"photo/character/return.png",
		CC_CALLBACK_1(ChooseCharacter::returnMainMenu, this)
	);
	
	m_pBowmanMII->setPosition(330, 390);
	m_pSavageMII->setPosition(550, 390);
	m_pWizardMII->setPosition(770, 390);
	ChooseMII->setPosition(700, 50);
	ReturnMII->setPosition(330, 50);

	Menu *pMenu = Menu::create(m_pBowmanMII, m_pSavageMII,m_pWizardMII,ChooseMII,ReturnMII,NULL);
	pMenu->setPosition(Vec2::ZERO);
	addChild(pMenu, 1);

	return true;
}

void ChooseCharacter::BowmanIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(false);
	m_pSavageMII->setEnabled(true);
	m_pWizardMII->setEnabled(true);
	m_pBowmanIntro->setVisible(true);
	m_pSavageIntro->setVisible(false);
	m_pWizardIntro->setVisible(false);
	ChooseHero = 1;
}

void ChooseCharacter::SavageIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(true);
	m_pSavageMII->setEnabled(false);
	m_pWizardMII->setEnabled(true);
	m_pBowmanIntro->setVisible(false);
	m_pSavageIntro->setVisible(true);
	m_pWizardIntro->setVisible(false);
	ChooseHero = 2;
}

void ChooseCharacter::WizardIntro(cocos2d::Ref * pSender)
{
	m_pBowmanMII->setEnabled(true);
	m_pSavageMII->setEnabled(true);
	m_pWizardMII->setEnabled(false);
	m_pBowmanIntro->setVisible(false);
	m_pSavageIntro->setVisible(false);
	m_pWizardIntro->setVisible(true);
	ChooseHero = 3;
}


void ChooseCharacter::enterGameCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect/button.mp3");

	if (!m_IsChangeScene)
	{
		/*Scene *scene = Scene::create();
		GameScene2 *layer = GameScene2::create();
		layer->myChoice= ChooseHero;
		scene->addChild(layer);
		Director::sharedDirector()->replaceScene(TransitionFade::create(1, scene));*/
        //Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
		myChoice = ChooseHero;
		TransitionScene * reScene = NULL;
		
		connectToServer();
		std::string heroNum = "e";
		heroNum += to_string(myChoice);
		heroNum.push_back('*');
		const char* eneNum = heroNum.c_str();
		
		send(_sock, eneNum, heroNum.size()+1, 0);

		while (1) {
			char recvFser[100] = {};
			recv(_sock, recvFser, 100, 0);
			if (recvFser[0] == 'u') {
				side = recvFser[1] - '0';
				eneChoice = recvFser[2] - '0';
				break;
			}
		}

		Scene *pScene = GameScene2::createScene();
		reScene = TransitionCrossFade::create(0.8f, pScene);
		Director::getInstance()->replaceScene(reScene);
		m_IsChangeScene = true;
	}
}

void ChooseCharacter::returnMainMenu(cocos2d::Ref * pSender)
{
	TransitionScene * reScene = NULL;
	Scene *pScene = Avene::createScene();
	reScene = TransitionCrossFade::create(0.8f, pScene);
	Director::getInstance()->replaceScene(reScene);
	m_IsChangeScene = true;
}

void ChooseCharacter::update(float delta)
{
}




