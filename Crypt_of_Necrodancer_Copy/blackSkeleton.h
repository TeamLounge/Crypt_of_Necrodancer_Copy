#pragma once
#include "skeleton.h"
class blackSkeleton : public skeleton
{
	image *_heart1, *_heart2, *_heart3;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render(int tileX, int tileY);
};

