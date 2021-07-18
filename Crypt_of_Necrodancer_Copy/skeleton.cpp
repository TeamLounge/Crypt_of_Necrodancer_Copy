#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init()
{
	
	isRight = true;

	return S_OK;
}

void skeleton::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_direction = RIGHT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_direction = LEFT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_direction = UP;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_direction = DOWN;
	}

	skeletonMove();
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
	RECT rcCollision;

	int tilecollsionX[2];
	int tilecollsionY[2];
	int tileX, tileY;

	rcCollision = _rc;

	switch (_direction)
	{
	case RIGHT:
		_x += TILESIZE;
		rcCollision = RectMakeCenter(_x, _y, TILESIZE - 5, TILESIZE - 5);
		break;
	case LEFT:
		_x -= TILESIZE;
		rcCollision = RectMakeCenter(_x, _y, TILESIZE - 5, TILESIZE - 5);
		break;
	case UP:
		_y -= TILESIZE;
		rcCollision = RectMakeCenter(_x, _y, TILESIZE - 5, TILESIZE - 5);
		break;
	case DOWN:
		_y += TILESIZE;
		rcCollision = RectMakeCenter(_x, _y, TILESIZE - 5, TILESIZE - 5);
		break;
	}

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_direction)
	{
	case RIGHT:
		tilecollsionX[0]= tileX+1;
		tilecollsionY[0]= tileY;
		tilecollsionX[1] = tileX + 1;
		tilecollsionY[1] = tileY +1;
		break;
	case LEFT:
		tilecollsionX[0] = tileX;
		tilecollsionY[0] = tileY;
		tilecollsionX[1] = tileX;
		tilecollsionY[1] = tileY + 1;
		break;
	case UP:
		tilecollsionX[0] = tileX;
		tilecollsionY[0] = tileY;
		tilecollsionX[1] = tileX + 1;
		tilecollsionY[1] = tileY;
		break;
	case DOWN:
		tilecollsionX[0] = tileX;
		tilecollsionY[0] = tileY+1;
		tilecollsionX[1] = tileX +1 ;
		tilecollsionY[1] = tileY +1;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;

		if ((_tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].obj == WALL_BASIC) &&
			(_tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].obj == WALL_GOLD) &&
			(_tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].obj == WALL_END) &&
			IntersectRect(&rc, &_tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
			case RIGHT:
				_rc.right = _tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].rc.left;
				_rc.left = _rc.right - (TILESIZE - 5);

				_x = (_rc.right + _rc.left) / 2;
				break;
			case LEFT:
				_rc.left = _tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].rc.right;
				_rc.right = _rc.left + (TILESIZE - 5);

				_x = (_rc.right + _rc.left) / 2;
				break;
			case UP:
				_rc.top = _tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].rc.bottom;
				_rc.bottom = _rc.top + (TILESIZE - 5);

				_y = (_rc.top + _rc.bottom) / 2;
				break;
			case DOWN:
				_rc.bottom = _tilemap->getTiles()[tilecollsionX[i]][tilecollsionY[i]].rc.top;
				_rc.top = _rc.bottom - (TILESIZE - 5);

				_y = (_rc.top + _rc.bottom) / 2;
				break;
			}
		}
	}

	_rc = RectMakeCenter(_x, _y, TILESIZE - 5, TILESIZE - 5);
}