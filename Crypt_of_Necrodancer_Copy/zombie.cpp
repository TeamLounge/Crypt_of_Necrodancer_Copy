#include "stdafx.h"
#include "zombie.h"

HRESULT zombie::init()
{
	//��� init
	_toRender = _damageRender = false;
	_direction = (PLAYER_ENEMY_DIRECTION)RND->getFromIntTo(1, 4); //��� ����
	_frameCount = 0;
	_frameIndex = 0;

	_isMove = false;		//�������ڸ��� ������
	_isTime = false;

	_gravity = 0;

	_worldTime = TIMEMANAGER->getWorldTime();

	//�ʿ� �ѷ��ֱ�
	setArrangement();	//Ÿ�Ͽ� ���� �Ѹ���

	_img = IMAGEMANAGER->findImage("zombie");	//�ڽ�
	_rc = _map->getRect(_tileX, _tileY);
	_map->setIsEnemy(_tileX, _tileY, true);
	_x = _rc.left;
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	///////////////////////////////////////////////


	return S_OK;
}

void zombie::release()
{
}

void zombie::update()
{
	setZombieFrame();
	moveZombie();
}

void zombie::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}

void zombie::setArrangement()
{
	//���� ��ġ
	while (true)
	{
		//�����濡 ��ġ
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��

		//�����ϰ� ���� ����� ��ǥ �� ���� �־ ��Ƽ��
		_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1
			|| _map->getIsEnemy(_tileX, _tileY))		//���� tile�� 2����, room���� ��ġ�ϴϱ� ����!
			continue;
		break;		//// ��� ��Ƽ�� �������� ����ٸ� ���� ������
	}
}

void zombie::setZombieFrame()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
	}

	_frameCount++;
	if (_frameCount % 8 == 0)
	{
		_frameCount = 0;
		if (_currentFrameX >= IMAGEMANAGER->findImage("zombie")->getMaxFrameX())
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
			_currentFrameY = 2;
		}
		else if (_direction == DOWN)
		{
			_currentFrameY = 3;
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

void zombie::moveZombie()
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)	//2����
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

		//���� �ƴ� ���� => ������ �� �� �ٲ�
		if (!_isMove)
		{
			if (_direction == UP)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE || _map->getIsEnemy(_tileX, _tileY))	//pastX, pastY�� ���ʹ̰� �ƴ�(false)�� �˷������
				{
					_direction = DOWN;
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);	
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
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
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
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
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
					_map->setIsEnemy(_tileX, _tileY, true);
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileX += 1;
					_isMove = true;
				}

				_rc = _map->getRect(_tileX, _tileY);
				_map->setIsEnemy(_tileX, _tileY, true);
			}
		}
	}

	//���������� ������ �޷�����
	if (_isMove)	//_isMove�� ����
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
				_gravity = 0;
			}
			break;
		}
	}

	
	
}
