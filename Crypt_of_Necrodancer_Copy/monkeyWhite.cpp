#include "stdafx.h"
#include "monkeyWhite.h"

HRESULT monkeyWhite::init(int playerIndexX, int playerIndexY)
{
	monkey::init(playerIndexX, playerIndexY);
	_hp = 6;
	_img = IMAGEMANAGER->findImage("monkeyWhite");
	_img->setFrameY(0);
	return S_OK;
}

void monkeyWhite::update(int playerIndexX, int playerIndexY)
{
	monkey::update(playerIndexX, playerIndexY);

	if (_index <= 3)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 3) _index = 0;
			_count = 0;
		}
	}
	if (iscatch&&_index == 4)
	{
		_hp = 6;
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
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
			//_y -= 9;
		//_shadow.top -= -sinf(1 * PI / 2) * 6;
		//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
		//if (_shadow.top >= _tileRect.top - 13)
		//{
		//_shadow.top = _tileRect.top - 13;
		//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
				//_tileRenderY = _tileY;
			}
			break;
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			//_shadow.left += cosf(7 * PI / 9) * 9;
			//_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x <= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
				//_tileRenderX = _tileX;
			}
			//if (_shadow.left <= _tileRect.left)
			//{
			//	_shadow.left = _tileRect.left;
			//	_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			//}
			break;
		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			//_shadow.left -= cosf(7 * PI / 9) * 10;
			//_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			if (_x >= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{

					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
				//_tileRenderX = _tileX;
			}
			//if (_shadow.left >= _tileRect.left)
			//{
			//	_shadow.left = _tileRect.left;
			//	_shadow.right = _shadow.left + IMAGEMANAGER->findImage("player_shadow")->getWidth();
			//}

			break;
		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			//_y -= 9;
			//_shadow.top += -sinf(1 * PI / 2) * 6;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			//if (_shadow.top <= _tileRect.top - 13)
			//{
			//	_shadow.top = _tileRect.top - 13;
			//	_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
				//_tileRenderY = _tileY;
			}
			//}
			break;
		case DOWN:

			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;
			//_y -= 9;
			//_shadow.top -= -sinf(1 * PI / 2) * 6;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			//if (_shadow.top >= _tileRect.top - 13)
			//{
			//_shadow.top = _tileRect.top - 13;
			//_shadow.bottom = _shadow.top + IMAGEMANAGER->findImage("player_shadow")->getHeight();
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
				//_tileRenderY = _tileY;
			}
			//}
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

void monkeyWhite::release()
{
}

void monkeyWhite::render(int tileX, int tileY)
{
	if (tileX == _tilex && tileY == _tiley)
	{
		monkey::render();
		if (_map->getAlpha(_tilex, _tiley) <= 255 && _map->getAlpha(_tilex, _tiley) > 150) {
			_img = IMAGEMANAGER->findImage("monkeyWhite");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
		else if (_map->getAlpha(_tilex, _tiley) <= 150 && _map->getAlpha(_tilex, _tiley) > 0)
		{
			_img = IMAGEMANAGER->findImage("monkey_dark");
			_img->frameRender(getMemDC(), _x, _y, _index, _indey);
		}
	}
}
