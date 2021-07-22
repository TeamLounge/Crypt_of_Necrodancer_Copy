#include "stdafx.h"
#include "slimeBlue.h"

HRESULT slimeBlue::init()
{
	setImage();

	slime::init();	//»ó¼Ó

	_img = IMAGEMANAGER->findImage("slimeBlue");
	_img->setFrameY(RND->getFromIntTo(0, 1));

	return S_OK;
}

void slimeBlue::update()
{
	slimeMove();
	setSlimeFrame();
}

void slimeBlue::release()
{
}

void slimeBlue::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom - _rc.top) / 2, _currentFrameX, _currentFrameY);
}

void slimeBlue::setImage()
{
	IMAGEMANAGER->addFrameImage("slimeBlue", "image/enemy/slimeBlue.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeBlue_dark", "image/enemy/slimeBlue_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
}

void slimeBlue::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	if (_currentFrameX >= IMAGEMANAGER->findImage("slimeBlue")->getMaxFrameX())
	{
		_currentFrameX = 0;
	}
	else
	{
		_currentFrameX++;
	}
	if (_direction == LEFT)
	{
		_currentFrameY = 1;
	}
	else if (_direction == RIGHT)
	{
		_currentFrameY = 0;
	}
}
