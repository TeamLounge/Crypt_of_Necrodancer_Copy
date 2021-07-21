#pragma once
#include "gameNode.h"

class shovel;

class shovelType
{
protected:

public:
	virtual shovelType* inputHandle(shovel* shovel) = 0;
	virtual void update(shovel* shovel) = 0;
	virtual void enter(shovel* shovel) = 0;
	virtual void exit(shovel* shovel) = 0;
};

