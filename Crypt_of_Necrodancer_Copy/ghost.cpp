#include "stdafx.h"
#include "ghost.h"

HRESULT ghost::init(int playerIndexX, int playerIndexY)
{
	ghostAndMinic::init(playerIndexX, playerIndexY);
	_movingTime = TIMEMANAGER->getWorldTime();
	_hp = 1;
	_img = IMAGEMANAGER->findImage("ghost");
	_img->setFrameY(0);
	alpha = 100;
	return S_OK;
}

void ghost::update(int playerIndexX, int playerIndexY)
{
	ghostAndMinic::update(playerIndexX, playerIndexY);


	if (isFind)
	{
		alpha = 255;

	}

	_count++;
	
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 1) _index = 0;
		_count = 0;
	}
	

	if (isMove)
	{
		switch (_dir)
		{
		case NONE:

			isMove = false;
			break;
		case LEFT:
			_x -= 9;
			if (_x <= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
			
			}
			break;
		case RIGHT:
		
			_x +=  9;
			if (_x >= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
			
			}
			break;
		case UP:
			_y -= 9;
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
			}
			break;
		case DOWN:
			_y += 9;
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
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

void ghost::release()
{

}

void ghost::render()
{
	ghostAndMinic::render();
	if (_map->getAlpha(_tilex, _tiley) <= 255 && _map->getAlpha(_tilex, _tiley) > 150) {
		
		_img = IMAGEMANAGER->findImage("ghost");
		_img->alphaFrameRender(getMemDC(), _x, _y, _index, _indey,alpha);
	}
	else if (_map->getAlpha(_tilex, _tiley) <= 150 && _map->getAlpha(_tilex, _tiley) > 0)
	{
		_img = IMAGEMANAGER->findImage("ghost_dark");
		_img->frameRender(getMemDC(), _x, _y, _index, _indey);
	}
	//_img->alphaFrameRender(getMemDC(), _x, _y, _index, _indey, alpha);
}
