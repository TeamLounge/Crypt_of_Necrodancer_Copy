#pragma once
#include "minotaurAndDragon.h"
class minotaur : public minotaurAndDragon
{
	image *_heart1, *_heart2, *_heart3, *_heart4;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};

