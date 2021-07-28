#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY , bool boss)
{

	skeleton::init(playerIndexX, playerIndexY , boss);
	_renderTime = _movingTime = TIMEMANAGER->getWorldTime();
	_hp = 1;
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
	if (isMove)
	{
		switch (_dir)
		{
		case NONE:
			_gravity += 0.965f;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
			}
			break;
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
		
			if (_x <= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
			}
		
			break;
		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			if (_x >= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{

					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
				
			}

			break;
		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
	
			}

			break;
		case DOWN:

			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;
			
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
				
			}
			break;
		}
	}
	if (playerIndexX < _tilex)
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

void whiteSkeleton::render(int tileX, int tileY)
{
	if (tileX == _tilex && tileY == _tiley)
	{
		//Rectangle(getMemDC(), _rc);
		skeleton::render();
		if (_map->getAlpha(_tilex, _tiley) <= 255 && _map->getAlpha(_tilex, _tiley) > 150) {
			_img = IMAGEMANAGER->findImage("whiteSkeleton");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
		else if (_map->getAlpha(_tilex, _tiley) <= 150 && _map->getAlpha(_tilex, _tiley) > 0)
		{
			_img = IMAGEMANAGER->findImage("skeleton_dark");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
	}
}
