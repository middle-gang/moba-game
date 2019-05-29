#ifndef __MINION_H__  
#define __MINION_H__  

#include "cocos2d.h"  
#include "Object.h"
using namespace cocos2d;

class MinionController
{
	std::vector<ObjectBase> minion;
	int minion_hp=100;
	float minion_v=50;
	int minion_r=100;
	int minion_attack=10;
	bool aware[999];
	bool moving=false;
	ObjectBase ene[999];
	Vec2 MinionSpawn = Vec2(0, 0);
	Vec2 Destination = Vec2(1000, 473);
	Vec2 Plan[999];
public:
	MinionController() {
	}
	std::vector<ObjectBase>& Container();
	void MoveAndAttack();
	bool CheckAware(ObjectBase* Sub);
	Sprite* NewMinion(int n);
	void Stop();
	int flag;
};


#endif  
