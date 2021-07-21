#include "stdafx.h"
#include "blackSkeleton.h"

HRESULT blackSkeleton::init(int playerIndexX, int playerIndexY)
{
	IMAGEMANAGER->addFrameImage("greenSkeleton", "image/enemy/skeletonYellow.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	skeleton::init(playerIndexX, playerIndexY);
	_img = IMAGEMANAGER->findImage("whiteSkeleton");
	_img->setFrameY(0);

	return S_OK;
}

void blackSkeleton::update(int playerIndexX, int playerIndexY)
{
	skeleton::update(playerIndexX, playerIndexY);
	_count++;
	if (_count % 10 == 0)
	{
		_img->setFrameX(_index);
		_index++;
		if (_index > 3) _index = 0;
		_count = 0;
	}
}

void blackSkeleton::release()
{
}

void blackSkeleton::render()
{

}
