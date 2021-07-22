#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	setImage();

	slime::init();	//»ó¼Ó

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!
	//int a = RND->getFromIntTo(0, 1);
	_img->setFrameY(RND->getFromIntTo(0, 1));	//ÁÂ ¿ì ·£´ý!
	_indexSwitch = false;

	return S_OK;
}

void slimeGreen::update()
{
	slimeMove();
	setSlimeFrame();

}

void slimeGreen::release()
{
}

void slimeGreen::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom - _rc.top) / 2, _currentFrameX, _currentFrameY);
}

void slimeGreen::setImage()
{
	IMAGEMANAGER->addFrameImage("slimeGreen", "image/enemy/slimeGreen.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGreen_dark", "image/enemy/slimeGreen_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
}

void slimeGreen::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	if (_currentFrameX >= IMAGEMANAGER->findImage("slimeGreen")->getMaxFrameX())
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

	/*if (IMAGEMANAGER->findImage("slimeGreen")->getFrameY() == 0)
	{
		_frameCount++;
		if (_img->getFrameX() == _img->getMaxFrameX())
		{
			_img->setFrameX(0);
			_img->setFrameY(0);
			_frameCount = 0;
		}
	}
	else if (IMAGEMANAGER->findImage("slimeGreen")->getFrameY() == 1)
	{
		_frameCount++;
		if (_img->getFrameX() == _img->getMaxFrameX())
		{
			_img->setFrameX(0);
			_img->setFrameY(1);
			_frameCount = 0;
		}
	}*/

	/*_count++;
	if (_count >= 3)
	{
		_count = 0;
		if (getCurrentFrameX() == _img->getMaxFrameX())
		{
			setCurrentFrameX(0);
		}
		else
		{
			setCurrentFrameX(getCurrentFrameX() + 1);
		}
		setCurrentFrameY(1);
	}*/


	/*if(_currentFrameX >= IMAGEMANAGER->findImage("slimeGreen")->getMaxFrameX())
	{
		_count++;
		if (_count >= 3)
		{
			_count = 0;
			if (getCurrentFrameX() == _img->getMaxFrameX());
			{
				setCurrentFrameY(_img->getMaxFrameX());
			}
			else
			{
				setCurrentFrameX(_img->getCurrentFrameX() + 1);
			}
			setCurrentFrameY(1);
		}
	}*/


	/*_count++;
	if (_count % 10 == 0)
	{
		_count = 0;
		if (getcurrentframex() == _img->getmaxframex())
		{
			setcurrentframey(_img->getmaxframex());
		}
		else
		{
			setcurrentframex(getcurrentframex() + 1);
		}
		setcurrentframey(1);
	}*/

}
