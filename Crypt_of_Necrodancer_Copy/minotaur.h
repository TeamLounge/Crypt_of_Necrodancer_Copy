#pragma once
#include "minotaurAndDragon.h"
class minotaur : public minotaurAndDragon
{

public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};

