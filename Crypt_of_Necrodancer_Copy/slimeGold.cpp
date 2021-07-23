#include "stdafx.h"
#include "slimeGold.h"

HRESULT slimeGold::init()
{
	setImage();

	slime::init();	//상속

	_img = IMAGEMANAGER->findImage("slimeGold");
	_img->setFrameY(RND->getFromIntTo(0, 1));
	_map->setIsEnemy(_tileX, _tileY, true);	//에너미 타일 속성 ON

	_direction = RIGHT;

	return S_OK;
}

void slimeGold::update()
{
	setSlimeFrame();
	moveSlimeGold();
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

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
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

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
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
}

void slimeGold::moveSlimeGold()		//1박자 우, 아래, 좌, 위 .. 길 막으면 반박자마다 때림
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 0.5f)
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		
		if (!_isMove)
		{
			switch (_direction)
			{
			case LEFT:
				_isMove = true;
				_tileX -= 1;

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
				break;

			case RIGHT:
				_isMove = true;
				_tileX += 1;

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
				break;

			case UP:
				_isMove = true;
				_tileY -= 1;

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
				break;

			case DOWN:
				_isMove = true;
				_tileY += 1;

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
				break;
			}
		}
	}
	//장애물이나 에너미 있으면 움직이지 않고 제자리 뛰기 만들어야함
	/////////////////////////////////////////////////////

	if (TIMEMANAGER->getWorldTime() - _renderTime >= 0.5f)	//1박자
	{
		_renderTime = TIMEMANAGER->getWorldTime();
		if (_toRender)
		{
			_toRender = false;
		}
		else
		{
			_toRender = true;
		}
	}

	//점프
	if (_isMove)	//RIGHT -> DOWN -> LEFT -> UP -> RIGHT ..순서
	{
		switch (_direction)
		{
		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;

			if (_x <= _rc.left)
			{
				_x = _rc.left;
				_isMove = false;
				_direction = UP;		//LEFT -> UP
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
				_isMove = false;
				_direction = DOWN;		//RIGHT -> DOWN
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
				_isMove = false;
				_direction = RIGHT;		//UP -> RIGHT
				_gravity = 0;
			}
			break;

		case DOWN:
			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;

			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				_isMove = false;
				_direction = LEFT;		//DOWN -> LEFT
				_gravity = 0;
			}
			break;
		}
	}
}
