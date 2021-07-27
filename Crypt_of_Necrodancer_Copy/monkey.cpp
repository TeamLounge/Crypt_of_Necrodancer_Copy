#include "stdafx.h"
#include "monkey.h"

HRESULT monkey::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	_count = _damageRenderCount = _damageindex = _index = _indey = 0;
	iscatch = damageRender = false;
	_beatspeed = 1.0f;
	while (true) //랜덤배치
	{
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// 그 방이 플레이어방이거나 상점이면 컨티뉴  
		_tilex = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tiley = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE || _map->getTileTerrain(_tilex, _tiley) != DIRT1 || _map->getIsEnemy(_tilex, _tiley))
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
	}
	_rc = _map->getRect(_tilex, _tiley);
	_map->setIsEnemy(_tilex, _tiley, true);
	_x = _rc.left;
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	_hp = 1;
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);
	return S_OK;
}

void monkey::update(int playerIndexX, int playerIndexY)
{
	
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatspeed/2)
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
	if (!iscatch && !isFind) {
		_astar->endmove(playerIndexX , playerIndexY);
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
	else if (!iscatch && isFind)
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
			monkeyMove(isTime);
		}
		if (_astar->getDamage())
		{
			_dir = _astar->getDirection();
			damageRender = true;
			_astar->setDamage(false);

		}
		isTime = false;
	}

	if (damageRender)
	{
		_map->setIsEnemy(_tilex, _tiley, false);
		switch (_dir)
		{
		case LEFT:
			_tilex -= 1;
			break;
		case RIGHT:
			_tilex += 1;
			break;
		case UP:
			_tiley -= 1;
			break;
		case DOWN:
			_tiley += 1;
			break;
		}
		_rc = _map->getRect(_tilex, _tiley);
		_map->setIsEnemy(_tilex, _tiley, true);
		_index = 4;
		iscatch = true;
		delete _astar;
		damageRender = false;
	}

}

void monkey::release()
{
}

void monkey::render()
{
	if (!iscatch) {
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			_astar->render();
		}
	}
	if (iscatch)
	{
		char str[20];
		sprintf_s(str, "hp:%d", _hp);
		TextOut(getMemDC(), _rc.left, _rc.top, str, strlen(str));
	}
	
}

void monkey::monkeyMove(bool Time)
{
	if (Time) {
		int pastX = _tilex;
		int pastY = _tiley;
		if (_astar->getCloseListsize() != 0)
		{
			if (_map->getTileObject(_astar->getClosebackX(), _astar->getClosebackY()) != WALL_DOOR &&
				!_map->getIsEnemy(_astar->getClosebackX(), _astar->getClosebackY()))
			{
				_map->setIsEnemy(_tilex, _tiley, false);
				_tilex = _astar->getClosebackX();
				_tiley = _astar->getClosebackY();
				_astar->move(_tilex, _tiley);
				_map->setIsEnemy(_tilex, _tiley, true);
			}
		}
		else if (_astar->getCloseListsize() == 0)
		{
			_astar->enemyAttack();
		}
		_rc = _map->getRect(_tilex, _tiley);
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

		isMove = true;
	}
}
