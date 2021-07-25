#include "stdafx.h"
#include "slimeGold.h"

HRESULT slimeGold::init()
{

	slime::init();	//���

	_direction = RIGHT;		//slimeGold�� �׻� �������� ���� ����

	_img = IMAGEMANAGER->findImage("slimeGold");
	_map->setIsEnemy(_tileX, _tileY, true);	//���ʹ� Ÿ�� �Ӽ� ON

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
		//���� �ٲ� �����ֱ�
		if (_direction == UP)
		{
			_currentFrameY = 1;
		}
		else if (_direction == DOWN)
		{
			_currentFrameY = 0;
		}
		if (_direction == LEFT)
		{
			_currentFrameY = 0;
		}
		else if (_direction == RIGHT)
		{
			_currentFrameY = 1;
		}
	}
}

void slimeGold::moveSlimeGold()		//1���� ��, �Ʒ�, ��, �� .. �� ������ �ݹ��ڸ��� ����
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 0.5f)	//1����
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		//������ Ÿ���� isEnemy�� ���� �� ���� false��
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

		if (!_isMove)
		{
			if (_direction == UP)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE || _map->getIsEnemy(_tileX, _tileY))
				{
					_direction = DOWN;
					_map->setTileObject(_tileX, _tileY + 1, OBJ_NONE, 0, 0);
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_tileY -= 1;
					_isMove = true;
				}

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
			}
			else if (_direction == DOWN)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY + 1);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE || _map->getIsEnemy(_tileX, _tileY))
				{
					_direction = UP;
					_map->setTileObject(_tileX, _tileY - 1, OBJ_NONE, 0, 0);
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_tileY += 1;
					_isMove = true;
				}

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
			}
			else if (_direction == LEFT)
			{
				OBJECT obj = _map->getTileObject(_tileX - 1, _tileY);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE || _map->getIsEnemy(_tileX, _tileY))
				{
					_direction = RIGHT;
					_map->setTileObject(_tileX + 1, _tileY, OBJ_NONE, 0, 0);
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_tileX -= 1;
					_isMove = true;
				}

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
			}
			else if (_direction == RIGHT)
			{
				OBJECT obj = _map->getTileObject(_tileX + 1, _tileY);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE || _map->getIsEnemy(_tileX, _tileY))
				{
					_direction = LEFT;
					_map->setTileObject(_tileX - 1, _tileY, OBJ_NONE, 0, 0);
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_tileX += 1;
					_isMove = true;
				}
				/*if (true)
				{

				}*/

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
			}
			
		}
	}
	//��ֹ��̳� ���ʹ� ������ �������� �ʰ� ���ڸ� �ٱ� ��������
	/////////////////////////////////////////////////////

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

	//����
	if (_isMove)	//RIGHT -> DOWN -> LEFT -> UP -> RIGHT ..����
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
