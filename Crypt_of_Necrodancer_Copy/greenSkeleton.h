#pragma once
#include "skeleton.h"

class greenSkeleton : public skeleton
{
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};