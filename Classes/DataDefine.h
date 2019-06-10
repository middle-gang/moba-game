#ifndef AFX_DATADEFINE
#define AFX_DATADEFINE

#include <cocos2d.h>

struct EquipmentData
{
	cocos2d::Sprite *pSprite;
	cocos2d::MenuItemImage *pMenuItemImage;	

	int buymoney;  //买入
	int sellmoney;  //售出

	int health;//生命值
	int magicpoint;//法力值
	int healthRecover;//生命回复
	int magicpointRecover;//法力回复
	float attack;//攻击力
	float power;//法术强度
	
	float armor;//护甲值
	float magicDenfence;//魔抗
	float armorIgnore;//护甲穿透
	float magicdenfenceIgnore;//法术穿透
	float physicBloodSuck;//物理吸血(此项按百分比计算）
	float magicBloodSuck;//法术吸血（百分比）
	float waitLessen;//冷却缩减(此项按百分比计算）

	float velocity;//移动速度
	float attackingSpeed;  //攻击速度
	float damageChance;//暴击几率
};


#endif
