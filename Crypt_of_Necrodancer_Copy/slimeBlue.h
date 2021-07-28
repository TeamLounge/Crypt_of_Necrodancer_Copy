#pragma once
#include "slime.h"

class slimeBlue :public slime
{
	image *_heart1, *_heart2;
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render(int tileX, int tileY);

	virtual void setSlimeFrame();
	virtual void moveSlimeBlue();
	virtual void attackPlayerRender();
};

