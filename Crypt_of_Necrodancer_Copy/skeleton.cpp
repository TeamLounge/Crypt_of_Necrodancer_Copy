#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init(int playerIndexX, int playerIndexY)
{
	_astar = new aStarTest;
	isFind = false;
	isTime = false;
	_count = _index = _indey = 0;
	toRender = false;
	while (true) //������ġ
	{
		int random = RND->getInt(_map->getRoom().size());//�����濡 ��ġ
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��  
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y) != OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue; //�����ϰ� ���� ����� ��ǥ �� �����־ ��Ƽ��
		break;//// ��� ��Ƽ�� �������� ����ٸ� ����������
	}
	_rc = _map->getRect(_x, _y);
	_map->setTileObject(_x, _y, ENEMY);
	_astar->setLinkrandomMap(_map);
	_astar->init(_x, _y, playerIndexX, playerIndexY);
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


	for (int y = _y - 3; y <= _y + 3; y++)
	{
		for (int x = _x - 3; x <= _x + 3; x++)
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
	_map->setTileObject(_x, _y, OBJ_NONE);
	_x = _astar->getenemyTileX();
	_y = _astar->getenemyTileY();
	_rc = _map->getRect(_x, _y);
	_map->setTileObject(_x, _y, ENEMY);
}