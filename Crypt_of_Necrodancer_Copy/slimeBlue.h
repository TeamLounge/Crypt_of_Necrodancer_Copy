#pragma once
#include "slime.h"

class slimeBlue :public slime
{
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void setImage();
	virtual void setSlimeFrame();
};

