#pragma once
#include "gameNode.h"

class weapon;

class weaponType
{
protected:

public:
	virtual weaponType* inputHandle(weapon* weapon) = 0;
	virtual void update(weapon* weapon) = 0;
	virtual void enter(weapon* weapon) = 0;
	virtual void exit(weapon* weapon) = 0;
};

