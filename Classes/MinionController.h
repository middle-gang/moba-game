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
	int minion_r=20;
	int minion_attack=50;
	bool moving=false;
	ObjectBase ene[999];
	Vec2 MinionSpawn;
	Vec2 Destination = Vec2(1000, 0);
	Vec2 Plan[999];
	float attackingDelayTime[999] = {0};
public:
	MinionController() {
	}
	std::vector<ObjectBase>& Container();
	void MoveToTarget();
	void Judge(int i, float delt);
	void setminionSpawn(Vec2 pos) {
		MinionSpawn = pos;
	}
	void setminionDes(Vec2 pos) {
		Destination = pos;
	}
	bool CheckAware(ObjectBase& Sub);
	Sprite* NewMinion();
	void Stop();
	void minionInit(ObjectBase& mini) {
		mini.AttackPower() = minion_attack;
		mini.totalHealth() = minion_hp;
		mini.healthPower() = minion_hp;
		mini.getRadium() = minion_r;
		mini.setVelocity(minion_v);
	}
	Vec2& getPlan(int i) {
		return Plan[i];
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
