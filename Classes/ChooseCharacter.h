#ifndef __ChooseCharacter_H__
#define __ChooseCharacter_H__

#include "cocos2d.h"
#include"GameScene2.h"

class ChooseCharacter : public cocos2d::Layer
{
public:
	int ChooseHero;
private:
	cocos2d::Sprite* m_pBowmanIntro;
	cocos2d::Sprite* m_pSavageIntro;
	cocos2d::Sprite* m_pWizardIntro;

	cocos2d::MenuItemImage* m_pBowmanMII;
	cocos2d::MenuItemImage* m_pSavageMII;
	cocos2d::MenuItemImage* m_pWizardMII;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void BowmanIntro(cocos2d::Ref* pSender);
	void SavageIntro(cocos2d::Ref* pSender);
	void WizardIntro(cocos2d::Ref* pSender);
	void enterGameCallBack(cocos2d::Ref* pSender);
	void returnMainMenu(cocos2d::Ref* pSender);

private:
	bool m_IsChangeScene;


	cocos2d::Sprite *m_pMaskImage;
	virtual void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(ChooseCharacter);
};

#endif // __HELLOWORLD_SCENE_H__

