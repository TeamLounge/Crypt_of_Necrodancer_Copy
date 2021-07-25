#pragma once
#include "minotaurAndDragon.h"

class redDragon : public minotaurAndDragon
{
protected:
	bool isCursh, isRun;

public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void render();

	virtual void setArrangement();
	virtual void setRedDragonFrame();
	virtual void moveRedDragon();
};

