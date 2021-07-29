#pragma once
#include "weaponType.h"

class weapon;

class longSword : public weaponType
{
private:
	float elapsedTime;  //����Ʈ ȿ�� ����������
	float speed;		//����Ʈ �ӵ��� ����

public:
	virtual weaponType* inputHandle(weapon* weapon);
	virtual void update(weapon* weapon);
	virtual void enter(weapon* weapon);
	virtual void exit(weapon* weapon);
};

