#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init(int playerIndexX, int playerIndexY)
{
	slime::init(playerIndexX, playerIndexY);	//상속

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!
	_map->setIsEnemy(_tileX, _tileY, true);	//에너미 타일 속성 ON		//에너미끼리 안 겹치게		//지나온 타일이 없으니까 이렇게 초기화만 해주고 말아도 됨.
	_indexSwitch = false;
	_hp = 1;
	_heart = IMAGEMANAGER->findImage("Enemy_heart");
	return S_OK;
}

void slimeGreen::update(int playerIndexX, int playerIndexY)
{
	setSlimeFrame();
	moveSlimeGreen();	//그린슬라임만의 움직임


}

void slimeGreen::release()
{
}

void slimeGreen::render(int tileX, int tileY)
{
	if (tileX == _tileX && tileY == _tileY)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _rc);
		}

		//알파 값에 따른 블랙모드
		if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 150) {
			if (_hp == 1)
			{
				_heart = IMAGEMANAGER->findImage("Enemy_heart");
				_heart->frameRender(getMemDC(), _x + 20, _y - 30, 0, 0);
			}
			_img = IMAGEMANAGER->findImage("slimeGreen");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}
		else if (_map->getAlpha(_tileX, _tileY) <= 150 && _map->getAlpha(_tileX, _tileY) > 0)
		{
			if (_hp == 1)
			{
				_heart = IMAGEMANAGER->findImage("Enemy_heart");
				_heart->frameRender(getMemDC(), _x + 20, _y - 30, 0, 0);
			}
			_img = IMAGEMANAGER->findImage("slimeGreen_dark");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}
	}
}

void slimeGreen::setSlimeFrame()
{
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
	

	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed / 2)
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
