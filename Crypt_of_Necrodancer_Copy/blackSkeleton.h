#pragma once
#include "skeleton.h"
class blackSkeleton : public skeleton
{
public:
	HRESULT init();
	void update();
	void release();
	void render();
};

