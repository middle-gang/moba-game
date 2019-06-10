#ifndef AFX_DATADEFINE
#define AFX_DATADEFINE

#include <cocos2d.h>

struct EquipmentData
{
	cocos2d::Sprite *pSprite;
	cocos2d::MenuItemImage *pMenuItemImage;	

	int buymoney;  //����
	int sellmoney;  //�۳�

	int health;//����ֵ
	int magicpoint;//����ֵ
	int healthRecover;//�����ظ�
	int magicpointRecover;//�����ظ�
	float attack;//������
	float power;//����ǿ��
	
	float armor;//����ֵ
	float magicDenfence;//ħ��
	float armorIgnore;//���״�͸
	float magicdenfenceIgnore;//������͸
	float physicBloodSuck;//������Ѫ(����ٷֱȼ��㣩
	float magicBloodSuck;//������Ѫ���ٷֱȣ�
	float waitLessen;//��ȴ����(����ٷֱȼ��㣩

	float velocity;//�ƶ��ٶ�
	float attackingSpeed;  //�����ٶ�
	float damageChance;//��������
};


#endif
