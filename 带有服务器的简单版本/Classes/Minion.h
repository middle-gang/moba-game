#ifndef __MINION_H__  
#define __MINION_H__  

#include "cocos2d.h"  
#include "Object.h"
using namespace cocos2d;

class Minion : public ObjectBase
{
public:
	Minion(){
		Charac = Sprite::create("qian.png");
	}
	Minion(std::string str) {
		Charac = Sprite::create(str);
	}
	void minionMove(Vec2 des) {
		float ed = Position.distance(des);
		Charac->stopAllActions();
		Charac->runAction(MoveTo::create(ed / velocity, des));
	}
	void NearHeroAttack(ObjectBase& ene) {
		float edis = ene.getPosition().distance(Position);
		Destination = ene.getPosition();
		Attack(ene);
	}
private:
	Vec2 Destination=Position;
};

#endif  
