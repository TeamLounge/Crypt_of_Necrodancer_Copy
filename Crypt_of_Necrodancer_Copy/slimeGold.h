#pragma once
#include "slime.h"

class slimeGold :public slime
{
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

