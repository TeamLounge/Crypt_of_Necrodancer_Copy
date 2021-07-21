#pragma once
#include "shovelType.h"

class shovel;

class shovelTitanium : public shovelType
{
public:
	virtual shovelType* inputHandle(shovel* shovel);
	virtual void update(shovel* shovel);
	virtual void enter(shovel* shovel);
	virtual void exit(shovel* shovel);
};

