#pragma once
#include "slime.h"

class slimeGreen :public slime
{
public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};