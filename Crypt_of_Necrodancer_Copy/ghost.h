#pragma once
#include "ghostAndMinic.h"

class ghost : public ghostAndMinic
{
private:
	int alpha;
public:
	HRESULT init(int playerIndexX, int playerIndexY , int x = 0,int y = 0,bool boss = false );
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};

