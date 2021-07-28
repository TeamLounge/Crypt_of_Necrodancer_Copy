#pragma once
#include "skeleton.h"

class whiteSkeleton : public skeleton
{
	bool _indexswitch;
public:
	HRESULT init(int playerIndexX , int playerIndexY , bool boss = false);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);

};