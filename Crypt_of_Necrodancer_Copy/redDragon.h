#pragma once
#include "minotaurAndDragon.h"

class redDragon : public minotaurAndDragon
{
protected:
	bool isCursh, isRun;
	bool isSameLine;	// �÷��̾�� ���� ���� ���̾�?

public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void release();
	void update(int playerIndexX, int playerIndexY);
	void render(int tileX, int tileY);

	virtual void setRedDragonFrame();
	virtual void moveRedDragon();
};

