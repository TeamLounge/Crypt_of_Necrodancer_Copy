#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	slime::init();	//상속

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!
	_map->setIsEnemy(_tileX, _tileY, true);	//에너미 타일 속성 ON		//에너미끼리 안 겹치게
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

void slimeGreen::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	//지나온 타일의 isEnemy에 관한 불 값을 false로
	_pastX = _tileX;
	_pastY = _tileY;

	if (_pastY == _tileY && _tileX - _pastX == -1)
	{
		//_direction = LEFT;
		_map->setIsEnemy(_tileX, _tileY, false);
	}
	else if (_pastY == _tileY && _tileX - _pastX == 1)
	{
		//_direction = RIGHT;
		_map->setIsEnemy(_tileX, _tileY, false);
	}
	else if (_pastX == _tileX && _tileY - _pastY == -1)
	{
		//_direction = UP;
		_map->setIsEnemy(_tileX, _tileY, false);
	}
	else if (_pastX == _tileX && _tileY - _pastY == 1)
	{
		//_direction = DOWN;
		_map->setIsEnemy(_tileX, _tileY, false);
	}
	else if (_tileX == _pastX && _tileY == _pastY)
	{
		//_direction = NONE;
		_map->setIsEnemy(_tileX, _tileY, false);
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
	}
}

void slimeGreen::moveSlimeGreen()
{
	

	if (TIMEMANAGER->getWorldTime() - _movingTime >= 0.5f)	//2박자
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (_isTime)
		{
			_isTime = false;
			_isMove = true;
		}
		else
		{
			_isTime = true;
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
