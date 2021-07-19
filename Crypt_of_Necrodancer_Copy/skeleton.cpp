#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init()
{
	_direction = NONE;
	isRight = true;

	return S_OK;
}

void skeleton::update(int playerIndexX , int playerIndexY)
{
	
}

void skeleton::release()
{

}

void skeleton::render()
{
	_astar->render();
}

void skeleton::aStar()
{

}

void skeleton::skeletonMove()
{
	_x = _astar->getenemyTileX();
	_y = _astar->getenemyTileY();
	_rc = _map->getRect(_x, _y);
	//switch (direction)
	//{
	//case NONE:
	//	break;
	//
	//case RIGHT:
	//	if(_map->getTiles()[_y][_x + 1].obj == OBJ_NONE)
	//		_x += 1;
	//	_rc = _map->getTiles()[_y][_x].rc;
	//	break;
	//case LEFT:
	//	if (_map->getTiles()[_y][_x - 1].obj == OBJ_NONE)
	//		_x -= 1;
	//	_rc = _map->getTiles()[_y][_x].rc;
	//	break;
	//case UP:
	//	if (_map->getTiles()[_y-1][_x].obj == OBJ_NONE )
	//		_y -= 1;
	//	_rc = _map->getTiles()[_y][_x].rc;
	//	break;
	//case DOWN:
	//	if (_map->getTiles()[_y + 1][_x].obj == OBJ_NONE)
	//		_y += 1;
	//	_rc = _map->getTiles()[_y][_x].rc;
	//	break;
	//}
	//
}