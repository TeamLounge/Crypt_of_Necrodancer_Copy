#pragma once
#include "minotaurAndDragon.h"
class dragon : public minotaurAndDragon
{
private:
	bool isFire;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};

