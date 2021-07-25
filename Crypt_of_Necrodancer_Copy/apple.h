#pragma once
#include "foodType.h"

class food;

class apple : public foodType
{
private:

public:
	virtual foodType* inputHandle(food* food);
	virtual void update(food* food);
	virtual void enter(food* food);
	virtual void exit(food* food);
};

