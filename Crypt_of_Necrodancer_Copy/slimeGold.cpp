#include "stdafx.h"
#include "slimeGold.h"

HRESULT slimeGold::init()
{
	setImage();

	slime::init();	//»ó¼Ó

	_img = IMAGEMANAGER->findImage("slimeGold");
	_img->setFrameY(RND->getFromIntTo(0, 1));

	return S_OK;
}

void slimeGold::update()
{
	slimeMove();
	setSlimeFrame();
}

void slimeGold::release()
{
}

void slimeGold::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	IMAGEMANAGER->frameRender("slimeGold", getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom - _rc.top) / 2, _currentFrameX, _currentFrameY);
}

void slimeGold::setImage()
{
	IMAGEMANAGER->addFrameImage("slimeGold", "image/enemy/slimeGold.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGold_dark", "image/enemy/slimeGold_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
}

void slimeGold::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	if (_currentFrameX >= IMAGEMANAGER->findImage("slimeGold")->getMaxFrameX())
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
