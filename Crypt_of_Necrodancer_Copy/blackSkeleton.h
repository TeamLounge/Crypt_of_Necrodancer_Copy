#pragma once
#include "skeleton.h"
class blackSkeleton : public skeleton
{
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};

