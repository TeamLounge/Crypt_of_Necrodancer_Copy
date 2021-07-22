#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY)
{

	skeleton::init(playerIndexX, playerIndexY);
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

void whiteSkeleton::release()
{


}

void whiteSkeleton::render()
{
	//Rectangle(getMemDC(), _rc);
	skeleton::render();
	_img->frameRender(getMemDC(), _x, _y ,_index ,_indey);
}
