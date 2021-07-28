#pragma once
#include "monkey.h"
class monkeyWhite :public monkey 
{
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};

