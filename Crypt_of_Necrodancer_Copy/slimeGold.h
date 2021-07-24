#pragma once
#include "slime.h"

class slimeGold :public slime
{
public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void setSlimeFrame();
	virtual void moveSlimeGold();
};

