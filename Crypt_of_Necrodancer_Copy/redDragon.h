#pragma once
#include "minotaurAndDragon.h"

class redDragon : public minotaurAndDragon
{
protected:
	bool isCursh, isRun;
	bool isSameLine;	// 플레이어와 같은 가로 줄이야?

public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void release();
	void update(int playerIndexX, int playerIndexY);
	void render();

	virtual void setRedDragonFrame();
	virtual void moveRedDragon();
};

