#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	setImage();

	slime::init();	//상속

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!
	//int a = RND->getFromIntTo(0, 1);
	_img->setFrameY(RND->getFromIntTo(0, 1));	//좌 우 랜덤!
	_indexSwitch = false;

	return S_OK;
}

void slimeGreen::update()
{
	setSlimeFrame();
	moveSlimeGreen();	//그린슬라임만의 움직임

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

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
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

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("slimeGreen")->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		else
		{
			_currentFrameX++;
		}
		//좌우 랜덤 생성 어떻게 할까
		/*if (RND->getFromIntTo(0, 1) == 1)
		{
			_currentFrameY = 1;
		}
		else if (RND->getFromIntTo(0, 1) == 0)
		{
			_currentFrameY = 0;
		}*/
	}

	

}

void slimeGreen::moveSlimeGreen()
{
	

	if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)	//2박자
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (_isTime)
		{
			_isTime = false;
			//_isMove = true;
		}
		else
		{
			_isTime = true;
			//_isMove = true;
		}

	}
	if (TIMEMANAGER->getWorldTime() - _renderTime >= 0.5f)	//1박자
	{
		_renderTime = TIMEMANAGER->getWorldTime();
		if (_toRender)
		{
			_toRender = false;
			_isMove = true;
		}
		else
		{
			_toRender = true;
			_isMove = true;
		}
	}

	//점프
	if (_isMove)
	{
		_gravity += 0.965f;
		_y += -sinf(7 * PI / 9) * 9 + _gravity;

		if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
		{
			_y = _rc.top - (_rc.bottom - _rc.top) / 2;
			_isMove = false;
			_gravity = 0;
		}
	}
}
