#pragma once
#include "slime.h"

class slimeGreen :public slime
{
	bool _indexSwitch;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void setSlimeFrame();
	virtual void moveSlimeGreen();
};