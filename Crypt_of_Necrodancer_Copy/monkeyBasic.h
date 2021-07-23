#pragma once
#include "monkey.h"
class monkeyBasic : public monkey
{
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};

