#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	_count = _index = 0;
	_worldTime = TIMEMANAGER->getWorldTime();
	while (true) //랜덤배치
	{
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// 그 방이 플레이어방이거나 상점이면 컨티뉴  
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y) != OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
	}
	_rc = _map->getRect(_x, _y);
	_astar->setLinkrandomMap(_map);
	_astar->init(_x, _y, playerIndexX, playerIndexY);
	return S_OK;
}

void skeleton::update(int playerIndexX , int playerIndexY)
{
	_astar->endmove(playerIndexX, playerIndexY);
	for (int y = _y - 3; y < _y + 3; y++)
	{
		for (int x = _x - 3; x < _x + 3; x++)
		{
			if (x == playerIndexX && y == playerIndexY)
			{
				isFind = true;
			}
		}
	}
	if (isFind)
	{
		_astar->update(1.0f);
		skeletonMove();
	}
}

void skeleton::release()
{

}

void skeleton::render()
{
	_astar->render();
}


void skeleton::skeletonMove()
{
	_x = _astar->getenemyTileX();
	_y = _astar->getenemyTileY();
	_rc = _map->getRect(_x, _y);
	
}