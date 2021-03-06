#include "stdafx.h"
#include "ghostAndMinic.h"

HRESULT ghostAndMinic::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	_count = _damageRenderCount = _damageindex = _index = _indey = 0;
	damageRender = false;
	attack = false;
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
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);

	return S_OK;
}

HRESULT ghostAndMinic::bossInit(int playerIndexX, int playerIndexY, int x, int y)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = isMove = false;
	_count = _damageRenderCount = _damageindex = _index = _indey = 0;
	damageRender = false;
	attack = false;
	_beatspeed = 1.0f;

	_tilex = x;
	_tiley = y;

	_rc = _map->getRect(_tilex, _tiley);
	_map->setIsEnemy(_tilex, _tiley, true);
	_x = _rc.left;
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);

	return S_OK;
}

void ghostAndMinic::update(int playerIndexX, int playerIndexY)
{
	if (TIMEMANAGER->getWorldTime() - _movingTime >= _beatspeed / 2)
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
		if (playerIndexY == _tiley && (playerIndexX == _tilex - 1 || playerIndexX == _tilex + 1) ||
			playerIndexX == _tilex && (playerIndexY == _tiley - 1 || playerIndexY == _tiley + 1))
			isFind = true;
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
			GhostAndMimicMove(isTime);
		}

		isTime = false;
	}
	if (_astar->getDamage())
	{
		damageRender = true;
		_astar->setDamage(false);
		//여기가 에너미가 플레이어한데 어택!
		if (!attack) attack = true;
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
}

void ghostAndMinic::release()
{
}

void ghostAndMinic::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_astar->render();
	}
	if (damageRender)
	{
		switch (_astar->getDirection())
		{
		case LEFT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				_map->getRect(_tilex, _tiley).left + (_map->getRect(_tilex, _tiley).left - _map->getRect(_tilex, _tiley).right) / 2, _map->getRect(_tilex, _tiley).top, _damageindex, 1);
			break;
		case RIGHT:
			IMAGEMANAGER->frameRender("enemyAttackX", getMemDC(),
				(_map->getRect(_tilex, _tiley).left + _map->getRect(_tilex, _tiley).right) / 2, _map->getRect(_tilex, _tiley).top, _damageindex, 0);
			break;
		case UP:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tilex, _tiley).left, _map->getRect(_tilex, _tiley).top + (_map->getRect(_tilex, _tiley).top - _map->getRect(_tilex, _tiley).bottom) / 2, _damageindex, 1);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tilex, _tiley).left, (_map->getRect(_tilex, _tiley).top + _map->getRect(_tilex, _tiley).bottom) / 2, _damageindex, 1);
			break;
		}
	}
}

void ghostAndMinic::GhostAndMimicMove(bool Time)
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
				_map->setIsEnemy(_tilex, _tiley, true);
				_astar->move(_tilex, _tiley);

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
