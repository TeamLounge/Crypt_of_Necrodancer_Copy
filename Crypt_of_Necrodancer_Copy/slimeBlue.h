#pragma once
#include "slime.h"

class slimeBlue :public slime
{
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render();

	virtual void setSlimeFrame();
	virtual void moveSlimeBlue();
};

