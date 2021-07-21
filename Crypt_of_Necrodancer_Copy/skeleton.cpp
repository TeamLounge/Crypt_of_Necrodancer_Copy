#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init(int playerIndexX, int playerIndexY)
{

	_astar = new aStarTest;
	isFind = false;
	isTime = false;
	_count = _damageRenderCount =_damageindex =_index = _indey = 0;
	toRender = damageRender = false;
	while (true) //랜덤배치
	{
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// 그 방이 플레이어방이거나 상점이면 컨티뉴  
		_tilex = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tiley = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tilex, _tiley) != OBJ_NONE || _map->getTileTerrain(_tilex, _tiley) != DIRT1)
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
	}
	_rc = _map->getRect(_tilex, _tiley);
	_map->setTileObject(_tilex, _tiley, ENEMY);
	_x = _rc.left;
	_y = _rc.top;
	_astar->setLinkrandomMap(_map);
	_astar->init(_tilex, _tiley, playerIndexX, playerIndexY);
	return S_OK;
}

void skeleton::update(int playerIndexX , int playerIndexY)
{
	_astar->endmove(playerIndexX, playerIndexY);
	
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
	if (TIMEMANAGER->getWorldTime() - _renderTime >= 0.5f)
	{
		_renderTime = TIMEMANAGER->getWorldTime();
		if (toRender)
		{
			toRender = false;
		}
		else
		{
			toRender = true;
		}
	}


	for (int y = _tiley - 3; y <= _tiley + 3; y++)
	{
		for (int x = _tilex - 3; x <= _tilex + 3; x++)
		{
			if (x == playerIndexX && y == playerIndexY)
			{
				isFind = true;
			}
		}
	}
	if (isFind)
	{
		_astar->update(isTime);
		skeletonMove();
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
}

void skeleton::release()
{

}

void skeleton::render()
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
				(_map->getRect(_tilex, _tiley).left+_map->getRect(_tilex, _tiley).right)/2, _map->getRect(_tilex, _tiley).top, _damageindex, 0);
			break;
		case UP:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tilex, _tiley).left, _map->getRect(_tilex, _tiley).top +(_map->getRect(_tilex, _tiley).top - _map->getRect(_tilex, _tiley).bottom) / 2, _damageindex, 1);
			break;
		case DOWN:
			IMAGEMANAGER->frameRender("enemyAttackY", getMemDC(),
				_map->getRect(_tilex, _tiley).left, (_map->getRect(_tilex, _tiley).top +_map->getRect(_tilex, _tiley).bottom)/2, _damageindex, 1);
			break;
		}

	}
}


void skeleton::skeletonMove()
{
	int pastX = _tilex;
	int pastY = _tiley;
	_map->setTileObject(_tilex, _tiley, OBJ_NONE);
	_tilex = _astar->getEnemyTileX();
	_tiley = _astar->getEnemyTileY();
	_rc = _map->getRect(_tilex, _tiley);
	if (_tilex - pastX == -1)
	{
		_dir = LEFT;
	}
	else if (_tilex - pastX == 1)
	{
		_dir = RIGHT;
	}
	else if (_tiley - pastY == -1)
	{
		_dir = UP;
	}
	else if (_tiley - pastY == 1)
	{	
		_dir = DOWN;
	}
	else if (_tilex == pastX && _tiley == pastY)
	{
		_dir = NONE;
	}
	_map->setTileObject(_tilex, _tiley, ENEMY);
}