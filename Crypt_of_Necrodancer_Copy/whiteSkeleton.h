#pragma once
#include "skeleton.h"

class whiteSkeleton : public skeleton
{
public:
	HRESULT init();
	void update();
	void release();
	void render();

};