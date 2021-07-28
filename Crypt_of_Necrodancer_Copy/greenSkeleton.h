#pragma once
#include "skeleton.h"
class greenSkeleton : public skeleton
{
	bool _indexswitch;
	image *_heart1 , *_heart2;
public:
	HRESULT init(int playerIndexX, int playerIndexY , bool boss = false);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};