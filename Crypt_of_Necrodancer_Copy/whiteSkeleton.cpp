#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY)
{

	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	skeleton::init(playerIndexX, playerIndexY);
	_renderTime = _movingTime = TIMEMANAGER->getWorldTime();
	_img = IMAGEMANAGER->findImage("whiteSkeleton");
	_img->setFrameY(0);
	return S_OK;
}

void whiteSkeleton::update(int playerIndexX, int playerIndexY)
{
	skeleton::update(playerIndexX, playerIndexY);
	

	if (isFind&&toRender)
	{
		if (_index >= 4)
		{
			_index = 0;
		}
		else
		{
			_index = 4;
		}
		toRender = false;
	}

	_count++;
	if (_index >= 4 &&_index<8)
	{
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 7) _index = 4;
			_count = 0;
		}
	}
	else if (_index >= 0 && _index<4)
	{
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 3) _index = 0;
			_count = 0;
		}
	}
	if (playerIndexX > _x)
	{
		_indey = 0;
	}
	else
	{
		_indey = 1;
	}
}

void whiteSkeleton::release()
{


}

void whiteSkeleton::render()
{
	//Rectangle(getMemDC(), _rc);
	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom-_rc.top)/2 ,_index ,_indey );
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		skeleton::render();
	}
}
