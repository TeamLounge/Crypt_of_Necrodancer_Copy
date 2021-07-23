#include "stdafx.h"
#include "slimeBlue.h"

HRESULT slimeBlue::init()
{
	setImage();

	slime::init();	//���

	_img = IMAGEMANAGER->findImage("slimeBlue");
	_img->setFrameY(RND->getFromIntTo(0, 1));
	_map->setIsEnemy(_tileX, _tileY, true);	//���ʹ� Ÿ�� �Ӽ� ON

	_direction = UP;

	return S_OK;
}

void slimeBlue::update()
{
	setSlimeFrame();
	moveSlimeBlue();
}

void slimeBlue::release()
{
}

void slimeBlue::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}

void slimeBlue::setImage()
{
	IMAGEMANAGER->addFrameImage("slimeBlue", "image/enemy/slimeBlue.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeBlue_dark", "image/enemy/slimeBlue_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
}

void slimeBlue::setSlimeFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("slimeBlue")->getMaxFrameX())
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

void slimeBlue::moveSlimeBlue()		//2���� �Ʒ�, ��, �Ʒ�, ��	.. �� ������ ���� ���ڿ� ����
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)	//2����
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		if (!_isMove)
		{
			switch (_direction)
			{
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
	if (TIMEMANAGER->getWorldTime() - _renderTime >= 0.5f)	//1����
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

	//���� & ������
	if (_isMove)
	{
		switch (_direction)
		{
		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				_isMove = false;
				_direction = DOWN;
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
				_direction = UP;
				_gravity = 0;
			}
			break;
		}
	}

	////�̰� �� �����ϰ� ���� ����ִ°ǵ�..
	//if (time) {
	//	int pastX = _tileX;
	//	int pastY = _tileY;
	//	_map->setIsEnemy(_tileX, _tileY, false);
	//	
	//	_rc = _map->getRect(_tileX, _tileY);

	//	if (pastY == _tileY && _tileX - pastX == -1)
	//	{
	//		_direction = LEFT;
	//	}
	//	else if (pastY == _tileY && _tileX - pastX == 1)
	//	{
	//		_direction = RIGHT;
	//	}
	//	else if (pastX == _tileX && _tileY - pastY == -1)
	//	{
	//		_direction = UP;
	//	}
	//	else if (pastX == _tileX && _tileY - pastY == 1)
	//	{
	//		_direction = DOWN;
	//	}
	//	else if (_tileX == pastX && _tileY == pastY)
	//	{
	//		_direction = NONE;
	//	}
	//	_map->setIsEnemy(_tileX, _tileY, true);
	//	_isMove = true;
	//}

	////Ʈ�� ������ �� �������� �̵�
	//if (_map->getTileObject(_tileX, _tileY) == TR_LEFT)
	//{
	//	_direction = LEFT;
	//	_map->setIsEnemy(_tileX, _tileY, false);
	//	_tileX -= 1;
	//	_rc = _map->getRect(_tileX, _tileY);
	//	_map->setIsEnemy(_tileX, _tileY, true);
	//	_isMove = true;
	//}
	//else if (_map->getTileObject(_tileX, _tileY) == TR_RIGHT)
	//{
	//	_direction = RIGHT;
	//	_map->setIsEnemy(_tileX, _tileY, false);
	//	_tileX += 1;
	//	_rc = _map->getRect(_tileX, _tileY);
	//	_map->setIsEnemy(_tileX, _tileY, true);
	//	_isMove = true;
	//}
	//else if (_map->getTileObject(_tileX, _tileY) == TR_UP)
	//{
	//	_direction = UP;
	//	_map->setIsEnemy(_tileX, _tileY, false);
	//	_tileY -= 1;
	//	_rc = _map->getRect(_tileX, _tileY);
	//	_map->setIsEnemy(_tileX, _tileY, true);
	//	_isMove = true;
	//}
	//else if (_map->getTileObject(_tileX, _tileY) == TR_DOWN)
	//{
	//	_direction = DOWN;
	//	_map->setIsEnemy(_tileX, _tileY, false);
	//	_tileY += 1;
	//	_rc = _map->getRect(_tileX, _tileY);
	//	_map->setIsEnemy(_tileX, _tileY, true);
	//	_isMove = true;
	//}


}
