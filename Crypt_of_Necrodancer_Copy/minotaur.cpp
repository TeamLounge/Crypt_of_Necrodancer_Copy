#include "stdafx.h"
#include "minotaur.h"

HRESULT minotaur::init(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::init(playerIndexX, playerIndexY);
	_hp = 4;
	_img = IMAGEMANAGER->findImage("minotaur");
	_img->setFrameY(0);
	_x = (_rc.left+_rc.right)/2 - (_img->getFrameWidth()/2);
	_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	_gravity = 0;
	return S_OK;
}

void minotaur::update(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::update(playerIndexX, playerIndexY);

	if (_index <= 3) {
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 3) _index = 0;
			_count = 0;
		}
	}
	if (isAction&& _index >= 5)
	{
		if (isTime)
		{	
			_index++;
		}
		if (_index > 8)
		{
			_index = 0;
			isAction = false;
			_astar->callPathFinder(_tilex,_tiley);
		}
	}
	if (!isAction&&isFind)
	{
		//¾×¼Ç
		if (_tilex == playerIndexX)
		{
			_index == 4;
			if (_tiley > playerIndexY)
			{
				isAction = true;
				_index == 4;
				_dir = UP;
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
			}
			else if (_tiley < playerIndexY)
			{
				isAction = true;
			
				_index == 4;
				_dir = DOWN;
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
			}
		}
		else if (_tiley == playerIndexY)
		{
			if (_tilex > playerIndexX)
			{
				isAction = true;
				_index == 4;
				_dir = LEFT;
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
			}
			else if (_tilex < playerIndexX)
			{
				isAction = true;
				_index == 4;
				_dir = RIGHT;
				_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
				_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
			}
		}
	}
	moveMotion();
	if (playerIndexX < _tilex)
	{
		_indey = 0;
	}
	else
	{
		_indey = 1;
	}
	isTime = false;
}

void minotaur::release()
{
}

void minotaur::render(int tileX, int tileY)
{
	if (tileX == _tilex && tileY == _tiley)
	{
		minotaurAndDragon::render();
		//Rectangle(getMemDC(), _rc);

		if (_map->getAlpha(_tilex, _tiley) <= 255 && _map->getAlpha(_tilex, _tiley) > 150) {
			_img = IMAGEMANAGER->findImage("minotaur");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
		else if (_map->getAlpha(_tilex, _tiley) <= 150 && _map->getAlpha(_tilex, _tiley) > 0)
		{
			_img = IMAGEMANAGER->findImage("minotaur_dark");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
	}
}
