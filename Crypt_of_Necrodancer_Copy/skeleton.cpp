#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init()
{
	_astar = new aStarTest;
	_direction = NONE;
	isRight = true;

	return S_OK;
}

void skeleton::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_direction = RIGHT;
		skeletonMove();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_direction = LEFT;
		skeletonMove();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_direction = UP;
		skeletonMove();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_direction = DOWN;
		skeletonMove();
	}
	
}

void skeleton::release()
{

}

void skeleton::render()
{

}

void skeleton::aStar()
{
	
}

void skeleton::skeletonMove()
{

	switch (_direction)
	{
	case NONE:
		break;

	case RIGHT:
		if(_map->getTiles()[_y][_x + 1].obj == OBJ_NONE)
			_x += 1;
		_rc = _map->getTiles()[_y][_x].rc;
		break;
	case LEFT:
		if (_map->getTiles()[_y][_x - 1].obj == OBJ_NONE)
			_x -= 1;
		_rc = _map->getTiles()[_y][_x].rc;
		break;
	case UP:
		if (_map->getTiles()[_y-1][_x].obj == OBJ_NONE )
			_y -= 1;
		_rc = _map->getTiles()[_y][_x].rc;
		break;
	case DOWN:
		if (_map->getTiles()[_y + 1][_x].obj == OBJ_NONE)
			_y += 1;
		_rc = _map->getTiles()[_y][_x].rc;
		break;
	}





}