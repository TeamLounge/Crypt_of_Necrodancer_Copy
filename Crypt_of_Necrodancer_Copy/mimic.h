#pragma once
#include "ghostAndMinic.h"

class mimic : public ghostAndMinic
{
	image* _heart;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};