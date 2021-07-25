#pragma once
#include "gameNode.h"

class food;

class foodType
{
protected:


public:
	virtual foodType* inputHandle(food* food) = 0;
	virtual void update(food* food) = 0;
	virtual void enter(food* food) = 0;
	virtual void exit(food* food) = 0;
};

