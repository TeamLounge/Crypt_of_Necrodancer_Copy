#pragma once
#include "ghostAndMinic.h"

class ghost : public ghostAndMinic
{
private:
	int alpha;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};

