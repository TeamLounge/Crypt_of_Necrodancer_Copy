#pragma once
#include "minotaurAndDragon.h"

class redDragon : public minotaurAndDragon
{
protected:
	bool isCursh, isRun;
	bool isSameLine;	// 플레이어와 같은 가로 줄이야?
	image *_heart1, *_heart2, *_heart3, *_heart4 , *_heart5, *_heart6;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void release();
	void update(int playerIndexX, int playerIndexY);
	void render(int tileX, int tileY);

	virtual void setRedDragonFrame();
	virtual void moveRedDragon();
};

