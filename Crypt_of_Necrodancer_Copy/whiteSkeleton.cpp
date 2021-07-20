#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY)
{

	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	skeleton::init(playerIndexX, playerIndexY);
	_img = IMAGEMANAGER->findImage("whiteSkeleton");
	_img->setFrameY(0);

	return S_OK;
}

void whiteSkeleton::update(int playerIndexX, int playerIndexY)
{
	skeleton::update(playerIndexX, playerIndexY);
	_count++;
	if(_count%10==0)
	{
		_img->setFrameX(_index);
		_index++;
		if (_index > 3) _index = 0;
		_count = 0;
	}
}

void whiteSkeleton::release()
{


}

void whiteSkeleton::render()
{
	//Rectangle(getMemDC(), _rc);
	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom-_rc.top)/2);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		skeleton::render();
	}
}
