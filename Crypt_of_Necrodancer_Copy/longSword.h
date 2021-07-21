#pragma once
#include "weaponType.h"

class weapon;

class longSword : public weaponType
{
private:

public:
	virtual weaponType* inputHandle(weapon* weapon);
	virtual void update(weapon* weapon);
	virtual void enter(weapon* weapon);
	virtual void exit(weapon* weapon);
};

