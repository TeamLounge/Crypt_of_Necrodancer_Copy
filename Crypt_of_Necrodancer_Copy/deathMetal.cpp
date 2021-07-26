#include "stdafx.h"
#include "deathMetal.h"

HRESULT deathMetal::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	_responeCount = _count = _damageRenderCount = _damageindex = _index = _indey = _phase = 0;
	toRender = damageRender = false;
	_tilex =6; 
	_tiley =10;
	_rc = _map->getRect(_tilex, _tiley);		//_tileX, _tileY는 움직임을 위한 첫번째 타일맵의 좌표
	_map->setIsEnemy(_tilex, _tiley, true);
	_x = _rc.left;								//_x, _y는 이미지를 움직이기 위한 _rc를 토대로 가져온 실제 좌표(정보 가져오기 위함)
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);
	_playerindex = playerIndexX;
	_playerindey = playerIndexY;
	_hp = 9;
	return S_OK;
}

void deathMetal::update(int playerIndexX, int playerIndexY)
{
	_playerindex = playerIndexX;
	_playerindey = playerIndexY;
	if (TIMEMANAGER->getWorldTime() - _movingTime >= 1.0f)
	{
		_movingTime = TIMEMANAGER->getWorldTime();
		if (isTime)
		{
			isTime = false;
		}
		else
		{
			isTime = true;
		}

	}
	if (!isFind) {
		for (int y = _tiley - 4; y <= _tiley + 4; y++)
		{
			for (int x = _tilex - 4; x <= _tilex + 4; x++)
			{
				if (x == playerIndexX && y == playerIndexY)
				{
					isFind = true;
				}
			}
		}
	}
	else
	{
		_astar->endmove(playerIndexX, playerIndexY);
		_astar->update();

		if (_map->getTileObject(_tilex, _tiley) == TR_LEFT)
		{
			_dir = LEFT;
			_map->setIsEnemy(_tilex, _tiley, false);
			_tilex -= 1;
			_rc = _map->getRect(_tilex, _tiley);
			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
			//_astar->callPathFinder();
			isMove = true;
		}
		else if (_map->getTileObject(_tilex, _tiley) == TR_RIGHT)
		{
			_dir = RIGHT;
			_map->setIsEnemy(_tilex, _tiley, false);
			_tilex += 1;
			_rc = _map->getRect(_tilex, _tiley);
			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
			//_astar->callPathFinder();
			isMove = true;
		}
		else if (_map->getTileObject(_tilex, _tiley) == TR_UP)
		{
			_dir = UP;
			_map->setIsEnemy(_tilex, _tiley, false);
			_tiley -= 1;
			_rc = _map->getRect(_tilex, _tiley);
			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
			//_astar->callPathFinder();
			isMove = true;
		}
		else if (_map->getTileObject(_tilex, _tiley) == TR_DOWN)
		{
			_dir = DOWN;
			_map->setIsEnemy(_tilex, _tiley, false);
			_tilex += 1;
			_rc = _map->getRect(_tilex, _tiley);
			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
			//_astar->callPathFinder();
			isMove = true;
		}
		else if (_astar->getStart())
		{
			phaseOneMove(isTime);
		}

		isTime = false;
	}
	if (_astar->getDamage())
	{
		damageRender = true;
		_astar->setDamage(false);
	}

	if (damageRender)
	{
		_damageRenderCount++;
		if (_damageRenderCount % 3 == 0)
		{
			_damageindex++;
		}
		if (_damageindex > 4)
		{
			_damageindex = 0;
			damageRender = false;
		}
	}

	if (_hp >= 7)
	{
		switch (_dir)
		{
		case LEFT:
		case RIGHT:
			_index = 0;
			break;
		case UP:
			_index = 4;
			break;
		case DOWN:
			_index = 2;
			break;

		}
	}
	if (_hp < 7)
	{

	}
	if (playerIndexX < _tilex)
	{
		_indey = 0;
	}
	else
	{
		_indey = 1;
	}

	moveMotion();





}

void deathMetal::release()
{

}

void deathMetal::render()
{

}

void deathMetal::phaseOneMove(bool Time)
{
	if (Time) {
		++_responeCount;
		int pastX = _tilex;
		int pastY = _tiley;
		if (_astar->getCloseListsize() != 0)
		{
			if (!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex = _astar->getClosebackX();
				_tiley = _astar->getClosebackY();
				if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE)
				{
					_map->setTileObject(_tilex, _tiley, OBJ_NONE);
				}
				if (_map->getIsHaveTorch(_tilex, _tiley))
				{
					_map->setIsHaveTorch(_tilex, _tiley, false);
				}
				_rc = _map->getRect(_tilex, _tiley);

				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_dir = NONE;
		}
	}
	if (!isMove)isMove = true;
}

void deathMetal::phaseTwoMove(bool Time)
{
	if (Time) {
		int pastX = _tilex;
		int pastY = _tiley;
		int x = abs(_tilex - _playerindex);
		int y = abs(_tiley - _playerindey);
		if (x > 3)
		{
			if (_tilex > _playerindex)
			{
				_tilex += 1;
			}
			else
			{
				_tilex -= 1;
			}
		}
		if (y > 3)
		{
			if (_tiley > _playerindey)
			{
				_tiley += 1;
			}
			else
			{
				_tiley -= 1;
			}
		}
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE)
		{
			_map->setIsEnemy(_tilex, _tiley, false);
			_rc = _map->getRect(_tilex, _tiley);

			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
		}
		else
		{
			_tilex = pastX;
			_tiley = pastY;
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_dir = NONE;
		}
	}
	if (!isMove)isMove = true;

}

void deathMetal::phaseThreeMove(bool Time)
{
	if (Time) {
		int pastX = _tilex;
		int pastY = _tiley;
		int x = abs(_tilex - _playerindex);
		int y = abs(_tiley - _playerindey);
		if (x > 3)
		{
			if (_tilex > _playerindex)
			{
				_tilex += 1;
			}
			else
			{
				_tilex -= 1;
			}
		}
		if (y > 3)
		{
			if (_tiley > _playerindey)
			{
				_tiley += 1;
			}
			else
			{
				_tiley -= 1;
			}
		}
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE)
		{
			_map->setIsEnemy(_tilex, _tiley, false);
			_rc = _map->getRect(_tilex, _tiley);

			_astar->move(_tilex, _tiley);
			_map->setIsEnemy(_tilex, _tiley, true);
		}
		else
		{
			_tilex = pastX;
			_tiley = pastY;
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_dir = NONE;
		}
	}
	if (!isMove)isMove = true;
}

void deathMetal::phasefourMove(bool Time)
{
	if (Time) {
		int pastX = _tilex;
		int pastY = _tiley;
		if (_astar->getCloseListsize() != 0)
		{
			if (!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				if (_tilex != _playerindex)
				{
					_tilex = _astar->getClosebackX();
					_tiley = _astar->getClosebackY();
				}
				else
				{
					if (_tilex > _playerindex)
					{
						_tilex += 1;
					}
					else
					{
						_tilex -= 1;
					}
				}
				_rc = _map->getRect(_tilex, _tiley);

				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		if (pastY == _tiley && _tilex - pastX == -1)
		{
			_dir = LEFT;
		}
		else if (pastY == _tiley && _tilex - pastX == 1)
		{
			_dir = RIGHT;
		}
		else if (pastX == _tilex && _tiley - pastY == -1)
		{
			_dir = UP;
		}
		else if (pastX == _tilex && _tiley - pastY == 1)
		{
			_dir = DOWN;
		}
		else if (_tilex == pastX && _tiley == pastY)
		{
			_dir = NONE;
		}
	}
	if (!isMove)isMove = true;
}

void deathMetal::moveMotion()
{
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
}
