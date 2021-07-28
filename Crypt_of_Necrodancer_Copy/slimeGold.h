#pragma once
#include "slime.h"

class slimeGold :public slime
{
	image* _heart;
public:
	virtual HRESULT init(int playerIndexX, int playerIndexY);
	virtual void update(int playerIndexX, int playerIndexY);
	virtual void release();
	virtual void render(int tileX, int tileY);

	virtual void setSlimeFrame();
	virtual void moveSlimeGold();
	virtual void attackPlayerRender();
};

