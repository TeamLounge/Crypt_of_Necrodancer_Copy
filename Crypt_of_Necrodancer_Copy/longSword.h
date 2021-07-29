#pragma once
#include "weaponType.h"

class weapon;

class longSword : public weaponType
{
private:
	float elapsedTime;  //이펙트 효과 돌리기위한
	float speed;		//이펙트 속도를 위한

public:
	virtual weaponType* inputHandle(weapon* weapon);
	virtual void update(weapon* weapon);
	virtual void enter(weapon* weapon);
	virtual void exit(weapon* weapon);
};

