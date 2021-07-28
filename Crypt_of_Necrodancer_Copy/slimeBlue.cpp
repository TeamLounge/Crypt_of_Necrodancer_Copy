#include "stdafx.h"
#include "slimeBlue.h"

HRESULT slimeBlue::init(int playerIndexX, int playerIndexY)
{
	slime::init(playerIndexX, playerIndexY);	//���

	_img = IMAGEMANAGER->findImage("slimeBlue");
	_map->setIsEnemy(_tileX, _tileY, true);	//���ʹ� Ÿ�� �Ӽ� ON
	_hp = 2;
	_direction = UP;

	return S_OK;
}

void slimeBlue::update(int playerIndexX, int playerIndexY)
{
	_playerIndexX = playerIndexX;
	_playerIndexY = playerIndexY;

	setSlimeFrame();
	moveSlimeBlue();

	//���� Ÿ���� �÷��̾�� bool ���� true �Ǹ�
	if (_isPlayer)
	{
		_damageRenderCount++;
		if (_damageRenderCount % 3 == 0)
		{
			_damageIndex++;
			if (_damageIndex > 2)
			{
				_damageIndex = 0;
				_isPlayer = false;
			}
			_damageRenderCount = 0;
		}
	}
}

void slimeBlue::release()
{
}

void slimeBlue::render(int tileX, int tileY)
{
	if (tileX == _tileX && tileY == _tileY)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _rc);
		}

		//���� ���� ���� �����
		if (_map->getAlpha(_tileX, _tileY) <= 255 && _map->getAlpha(_tileX, _tileY) > 100) {
			_img = IMAGEMANAGER->findImage("slimeBlue");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}
		else if (_map->getAlpha(_tileX, _tileY) <= 100 && _map->getAlpha(_tileX, _tileY) > 0)
		{
			_img = IMAGEMANAGER->findImage("slimeBlue_dark");
			_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		}

		attackPlayerRender();
	}
}

void slimeBlue::setSlimeFrame()
{
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
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatSpeed)	//2����
	{
		_movingTime = TIMEMANAGER->getWorldTime();

		if (!_isMove)
		{
			if (_direction == NONE)
			{
				//UP
				if (_pastDirection == UP)
				{
					if (_tileX == _playerIndexX && _tileY - 1 == _playerIndexY)
					{

						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;
					}
					else
					{
						_direction = _pastDirection;
					}
				}
				//DOWN
				else if (_pastDirection == DOWN)
				{
					if (_tileX == _playerIndexX && _tileY + 1 == _playerIndexY)
					{
						if (!_isAttack)	_isAttack = true;
						_isPlayer = true;
					}
					else
					{
						_direction = _pastDirection;
					}
				}
			}

			if (_direction == UP)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY - 1);

				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE )
				{
					_direction = DOWN;
				}
				else if (_map->getIsEnemy(_tileX, _tileY - 1))		//���� Ÿ���� enemy�� ���ڸ� ����
				{
					_pastDirection = _direction;	//_past�� ���� ���� �ϴ� ����������.
					_direction = NONE;
				}
				//PLAYER �Ǵ�
				else if (_tileX == _playerIndexX && _tileY - 1 == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				////TRAP �Ǵ�
				//else if ()
				//{
				//
				//}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY -= 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
			else if (_direction == DOWN)
			{
				OBJECT obj = _map->getTileObject(_tileX, _tileY + 1);
				if (obj == WALL_CRACK || obj == WALL_END || obj == WALL_DOOR || obj == WALL_BASIC
					|| obj == WALL_GOLD || obj == WALL_STONE )
				{
					_direction = UP;
				}
				else if (_map->getIsEnemy(_tileX, _tileY + 1))
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else if (_tileX == _playerIndexX && _tileY + 1 == _playerIndexY)
				{
					_pastDirection = _direction;
					_direction = NONE;
				}
				else
				{
					_map->setIsEnemy(_tileX, _tileY, false);
					_tileY += 1;
					_isMove = true;
					_map->setIsEnemy(_tileX, _tileY, true);
				}

				_rc = _map->getRect(_tileX, _tileY);
			}
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

		case NONE:
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

void slimeBlue::attackPlayerRender()
{
	if (_isPlayer)
	{
		switch (_pastDirection)
		{
		case LEFT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				_map->getRect(_tileX, _tileY).left + (_map->getRect(_tileX, _tileY).left - _map->getRect(_tileX, _tileY).right) / 2, _map->getRect(_tileX, _tileY).top, _damageIndex, 1);
			break;
		case RIGHT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				(_map->getRect(_tileX, _tileY).left + _map->getRect(_tileX, _tileY).right) / 2, _map->getRect(_tileX, _tileY).top, _damageIndex, 0);
			break;
		case UP:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tileX, _tileY).left, _map->getRect(_tileX, _tileY).top + (_map->getRect(_tileX, _tileY).top - _map->getRect(_tileX, _tileY).bottom)* (3 / 2), _damageIndex, 1);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tileX, _tileY).left, (_map->getRect(_tileX, _tileY).top + _map->getRect(_tileX, _tileY).bottom) / 2, _damageIndex, 1);
			break;
		}
	}
}
