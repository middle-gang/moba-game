#ifndef AFX_DATADEFINE
#define AFX_DATADEFINE

#include <cocos2d.h>
class EquipmentData
{
public:
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

	std::vector<int> ingriEquip;
};


class Equipment
{
public:
	Equipment() {
		//属性
		s_Equip[1][0].attack = 20;
		s_Equip[1][1].attackingSpeed = 10;
		s_Equip[1][2].damageChance = 0.08;
		s_Equip[1][3].attack = 10;
		s_Equip[1][3].physicBloodSuck = 0.8;
		s_Equip[1][4].attack = 40;
		s_Equip[1][5].damageChance = 0.15;

		s_Equip[1][6].attack = 80;
		s_Equip[1][6].ingriEquip.push_back(100);/////////寻找是否可合成

		s_Equip[1][7].attack = 40;
		s_Equip[1][7].health = 300;
		s_Equip[1][7].ingriEquip.push_back(100);

		s_Equip[1][8].attackingSpeed = 15;
		s_Equip[1][8].damageChance = 0.1;
		s_Equip[1][8].velocity = 0.05;
		s_Equip[1][8].ingriEquip.push_back(101);
		s_Equip[1][8].ingriEquip.push_back(102);

		s_Equip[1][9].attack = 35;
		s_Equip[1][9].waitLessen = 0.1;
		s_Equip[1][9].armorIgnore = 60;
		s_Equip[1][9].magicdenfenceIgnore = 60;
		s_Equip[1][9].ingriEquip.push_back(100);

		s_Equip[1][10].attack = 80;
		s_Equip[1][10].waitLessen = 0.1;
		s_Equip[1][10].armorIgnore = 0.4;
		s_Equip[1][10].ingriEquip.push_back(100);

		s_Equip[1][11].attack = 60;
		s_Equip[1][11].attackingSpeed = 30;
		s_Equip[1][11].physicBloodSuck = 0.1;
		s_Equip[1][11].ingriEquip.push_back(114);

		s_Equip[1][12].attack = 60;
		s_Equip[1][12].waitLessen = 0.05;
		s_Equip[1][12].ingriEquip.push_back(100);
		s_Equip[1][12].ingriEquip.push_back(104);

		s_Equip[1][13].attack = 80;
		s_Equip[1][13].health = 600;
		s_Equip[1][13].ingriEquip.push_back(100);

		s_Equip[1][14].attackingSpeed = 25;
		s_Equip[1][14].attack = 30;
		s_Equip[1][14].power = 30;
		s_Equip[1][14].ingriEquip.push_back(101);

		s_Equip[1][15].attack = 100;
		s_Equip[1][15].magicBloodSuck = 0.1;
		s_Equip[1][8].ingriEquip.push_back(103);

		//金钱
		s_Equip[1][0].buymoney = 250;     s_Equip[1][0].sellmoney = 150;
		s_Equip[1][1].buymoney = 290;     s_Equip[1][1].sellmoney = 174;
		s_Equip[1][2].buymoney = 320;     s_Equip[1][2].sellmoney = 192;
		s_Equip[1][3].buymoney = 410;     s_Equip[1][3].sellmoney = 246;
		s_Equip[1][4].buymoney = 450;     s_Equip[1][4].sellmoney = 270;
		s_Equip[1][5].buymoney = 550;     s_Equip[1][5].sellmoney = 330;
		s_Equip[1][6].buymoney = 910;     s_Equip[1][6].sellmoney = 546;
		s_Equip[1][7].buymoney = 790;     s_Equip[1][7].sellmoney = 474;
		s_Equip[1][8].buymoney = 890;     s_Equip[1][8].sellmoney = 534;
		s_Equip[1][9].buymoney = 1048;     s_Equip[1][9].sellmoney = 648;
		s_Equip[1][10].buymoney = 2100;     s_Equip[1][10].sellmoney = 1260;
		s_Equip[1][11].buymoney = 2160;     s_Equip[1][11].sellmoney = 1296;
		s_Equip[1][12].buymoney = 1760;     s_Equip[1][12].sellmoney = 1056;
		s_Equip[1][13].buymoney = 1980;     s_Equip[1][13].sellmoney = 1188;
		s_Equip[1][14].buymoney = 890;     s_Equip[1][14].sellmoney = 534;
		s_Equip[1][15].buymoney = 1800;     s_Equip[1][15].sellmoney = 1080;

		///////////////////法术
		//属性
		s_Equip[2][0].power = 40;
		s_Equip[2][1].magicpoint = 300;
		s_Equip[2][2].magicpointRecover = 10;
		s_Equip[2][3].power = 20;
		s_Equip[2][3].waitLessen = 0.08;
		s_Equip[2][4].power = 80;

		s_Equip[2][5].power = 120;
		s_Equip[2][5].ingriEquip.push_back(200);

		s_Equip[2][6].power = 80;
		s_Equip[2][6].magicBloodSuck = 20;
		s_Equip[2][6].waitLessen = 0.05;
		s_Equip[2][6].ingriEquip.push_back(200);
		s_Equip[2][6].ingriEquip.push_back(202);

		s_Equip[2][7].health = 400;
		s_Equip[2][7].magicpoint = 400;
		s_Equip[2][7].ingriEquip.push_back(201);

		s_Equip[2][8].power = 70;
		s_Equip[2][8].health = 300;
		s_Equip[2][8].magicdenfenceIgnore = 75;
		s_Equip[2][8].ingriEquip.push_back(200);

		s_Equip[2][9].health = 400;
		s_Equip[2][9].magicpoint = 400;
		s_Equip[2][9].ingriEquip.push_back(201);

		s_Equip[2][10].power = 75;
		s_Equip[2][10].waitLessen = 0.1;
		s_Equip[2][10].magicBloodSuck = 0.2;
		s_Equip[2][10].ingriEquip.push_back(200);
		s_Equip[2][10].ingriEquip.push_back(203);

		s_Equip[2][11].power = 180;
		s_Equip[2][11].magicpoint = 600;
		s_Equip[2][11].magicpointRecover = 15;
		s_Equip[2][11].ingriEquip.push_back(201);
		s_Equip[2][11].ingriEquip.push_back(202);

		s_Equip[2][12].power = 240;
		s_Equip[2][12].velocity = 0.05;
		s_Equip[2][12].ingriEquip.push_back(204);

		s_Equip[2][13].power = 240;
		s_Equip[2][13].health = 300;
		s_Equip[2][13].magicdenfenceIgnore = 0.45;
		s_Equip[2][13].ingriEquip.push_back(212);

		s_Equip[2][14].power = 240.35;
		s_Equip[2][14].ingriEquip.push_back(205);

		s_Equip[2][15].power = 160;
		s_Equip[2][15].waitLessen = 0.1;
		s_Equip[2][15].ingriEquip.push_back(205);
		//金钱
		s_Equip[2][0].buymoney = 300;     s_Equip[2][0].sellmoney = 180;
		s_Equip[2][1].buymoney = 220;     s_Equip[2][1].sellmoney = 132;
		s_Equip[2][2].buymoney = 120;     s_Equip[2][2].sellmoney = 72;
		s_Equip[2][3].buymoney = 500;     s_Equip[2][3].sellmoney = 300;
		s_Equip[2][4].buymoney = 540;     s_Equip[2][4].sellmoney = 324;
		s_Equip[2][5].buymoney = 820;     s_Equip[2][5].sellmoney = 492;
		s_Equip[2][6].buymoney = 800;     s_Equip[2][6].sellmoney = 480;
		s_Equip[2][7].buymoney = 730;     s_Equip[2][7].sellmoney = 438;
		s_Equip[2][8].buymoney = 1020;     s_Equip[2][8].sellmoney = 612;
		s_Equip[2][9].buymoney = 720;     s_Equip[2][9].sellmoney = 432;
		s_Equip[2][10].buymoney = 1240;     s_Equip[2][10].sellmoney = 744;
		s_Equip[2][11].buymoney = 1950;     s_Equip[2][11].sellmoney = 1170;
		s_Equip[2][12].buymoney = 2050;     s_Equip[2][12].sellmoney = 1230;
		s_Equip[2][13].buymoney = 2110;     s_Equip[2][13].sellmoney = 1266;
		s_Equip[2][14].buymoney = 2300;     s_Equip[2][14].sellmoney = 1380;
		s_Equip[2][15].buymoney = 1990;     s_Equip[2][15].sellmoney = 1194;

		//////////////////防御
		s_Equip[3][0].health = 300;
		s_Equip[3][1].armor = 90;
		s_Equip[3][2].magicDenfence = 90;
		s_Equip[3][3].magicpointRecover = 30;

		s_Equip[3][4].health = 1000;
		s_Equip[3][4].ingriEquip.push_back(300);

		s_Equip[3][5].health = 700;
		s_Equip[3][5].ingriEquip.push_back(300);

		s_Equip[3][6].magicDenfence = 120;
		s_Equip[3][6].ingriEquip.push_back(300);
		s_Equip[3][6].health = 700;
		s_Equip[3][6].healthRecover = 50;
		s_Equip[3][6].ingriEquip.push_back(302);

		s_Equip[3][7].waitLessen = 0.1;
		s_Equip[3][7].magicpoint = 400;
		s_Equip[3][7].armor = 110;
		s_Equip[3][7].ingriEquip.push_back(301);

		s_Equip[3][8].armor = 210;
		s_Equip[3][8].ingriEquip.push_back(301);

		s_Equip[3][9].attack = 40;
		s_Equip[3][9].armor = 420;
		s_Equip[3][9].ingriEquip.push_back(301);

		s_Equip[3][10].attack = 20;
		s_Equip[3][10].health = 1000;

		s_Equip[3][11].armor = 240;
		s_Equip[3][11].health = 1000;
		s_Equip[3][11].ingriEquip.push_back(305);

		s_Equip[3][12].health = 2000;
		s_Equip[3][12].ingriEquip.push_back(304);

		s_Equip[3][13].armor = 270;
		s_Equip[3][13].health = 1200;
		s_Equip[3][13].ingriEquip.push_back(304);
		s_Equip[3][13].ingriEquip.push_back(308);

		s_Equip[3][14].healthRecover = 100;
		s_Equip[3][14].magicDenfence = 240;
		s_Equip[3][14].health = 1200;
		s_Equip[3][14].ingriEquip.push_back(306);

		s_Equip[3][15].magicDenfence = 360;
		s_Equip[3][15].health = 1000;
		s_Equip[3][15].ingriEquip.push_back(304);
		s_Equip[3][15].ingriEquip.push_back(306);

		//金钱
		s_Equip[3][0].buymoney = 300;     s_Equip[3][0].sellmoney = 180;
		s_Equip[3][1].buymoney = 220;     s_Equip[3][1].sellmoney = 132;
		s_Equip[3][2].buymoney = 220;     s_Equip[3][2].sellmoney = 132;
		s_Equip[3][3].buymoney = 140;     s_Equip[3][3].sellmoney = 84;
		s_Equip[3][4].buymoney = 900;     s_Equip[3][4].sellmoney = 540;
		s_Equip[3][5].buymoney = 900;     s_Equip[3][5].sellmoney = 540;
		s_Equip[3][6].buymoney = 1020;     s_Equip[3][6].sellmoney = 612;
		s_Equip[3][7].buymoney = 900;     s_Equip[3][7].sellmoney = 540;
		s_Equip[3][8].buymoney = 730;     s_Equip[3][8].sellmoney = 438;
		s_Equip[3][9].buymoney = 1840;     s_Equip[3][9].sellmoney = 1104;
		s_Equip[3][10].buymoney = 2120;     s_Equip[3][10].sellmoney = 1272;
		s_Equip[3][11].buymoney = 1830;     s_Equip[3][11].sellmoney = 1098;
		s_Equip[3][12].buymoney = 2070;     s_Equip[3][12].sellmoney = 1242;
		s_Equip[3][13].buymoney = 2180;     s_Equip[3][13].sellmoney = 1308;
		s_Equip[3][14].buymoney = 2100;     s_Equip[3][14].sellmoney = 1260;
		s_Equip[3][15].buymoney = 2120;     s_Equip[3][15].sellmoney = 1272;

		//////////////////移动
		s_Equip[4][0].velocity = 30;
		s_Equip[4][0].ingriEquip.push_back(400);

		s_Equip[4][1].armor = 110;
		s_Equip[4][1].velocity = 60;
		s_Equip[4][1].ingriEquip.push_back(400);

		s_Equip[4][2].magicDenfence = 110;
		s_Equip[4][2].ingriEquip.push_back(400);

		s_Equip[4][3].waitLessen = 0.15;
		s_Equip[4][3].ingriEquip.push_back(400);

		s_Equip[4][4].magicpointRecover = 25;
		s_Equip[4][4].velocity = 60;
		s_Equip[4][4].magicdenfenceIgnore = 75;
		s_Equip[4][4].ingriEquip.push_back(400);

		s_Equip[4][5].velocity = 60;
		s_Equip[4][5].attackingSpeed = 0.3;
		s_Equip[4][5].ingriEquip.push_back(400);

		s_Equip[4][6].velocity = 60;
		s_Equip[4][6].ingriEquip.push_back(400);

		//金钱
		s_Equip[4][0].buymoney = 250;     s_Equip[4][0].sellmoney = 150;
		s_Equip[4][1].buymoney = 710;     s_Equip[4][1].sellmoney = 426;
		s_Equip[4][2].buymoney = 710;     s_Equip[4][2].sellmoney = 426;
		s_Equip[4][3].buymoney = 710;     s_Equip[4][3].sellmoney = 426;
		s_Equip[4][4].buymoney = 710;     s_Equip[4][4].sellmoney = 426;
		s_Equip[4][5].buymoney = 710;     s_Equip[4][5].sellmoney = 426;
		s_Equip[4][6].buymoney = 530;     s_Equip[4][6].sellmoney = 318;

	}
	EquipmentData s_Equip[8][30];
	const EquipmentData findEquip(int n); //类别*100+编号
private:

};


#endif
