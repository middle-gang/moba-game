#include "DataDefine.h"

const EquipmentData Equipment::findEquip(int n){
	int f = n / 100;
	int b = n % 100;
	return s_Equip[f][b];
}