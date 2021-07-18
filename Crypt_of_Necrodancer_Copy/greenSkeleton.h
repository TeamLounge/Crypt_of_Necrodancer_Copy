#pragma once
#include "skeleton.h"

class greenSkeleton : public skeleton
{
public:
	HRESULT init();
	void update();
	void release();
	void render();
};