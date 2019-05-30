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
	Vec2 MinionSpawn;
	Vec2 Destination = Vec2(1000, 0);
	Vec2 Plan[999];
public:
	MinionController() {
	}
	std::vector<ObjectBase>& Container();
	void MoveAndAttack();
	void setminionSpawn(Vec2 pos) {
		MinionSpawn = pos;
	}
	void setminionDes(Vec2 pos) {
		Destination = pos;
	}
	bool CheckAware(ObjectBase* Sub);
	Sprite* NewMinion();
	void Stop();
	void minionInit(ObjectBase& mini) {
		mini.AttackPower() = minion_attack;
		mini.healthPower() = minion_hp;
		mini.getRadium() = minion_r;
		mini.setVelocity(minion_v);
	}
	Vec2 GetSpawn() {
		return MinionSpawn;
	}
	Vec2 GetDes() {
		return Destination;
	}
	int flag;
};


#endif  
