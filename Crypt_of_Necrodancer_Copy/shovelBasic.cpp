#include "stdafx.h"
#include "shovel.h"
#include "shovelBasic.h"
#include "shovelTitanium.h"
#include "player.h"

shovelType * shovelBasic::inputHandle(shovel * shovel)
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		return new shovelTitanium();
	}

	return nullptr;
}

void shovelBasic::update(shovel * shovel)
{
	if (shovel->_player->getDirection() == LEFT)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left - TILESIZE,
			shovel->_player->getTileRect().top,
			TILESIZE, TILESIZE);
	}

	if (shovel->_player->getDirection() == UP)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left,
			shovel->_player->getTileRect().top - TILESIZE,
			TILESIZE, TILESIZE);
	}

	if (shovel->_player->getDirection() == RIGHT)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left + TILESIZE,
			shovel->_player->getTileRect().top,
			TILESIZE, TILESIZE);
	}

	if (shovel->_player->getDirection() == DOWN)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left,
			shovel->_player->getTileRect().top + TILESIZE,
			TILESIZE, TILESIZE);
	}
}

void shovelBasic::enter(shovel * shovel)
{
	shovel->_vCollision.push_back(shovel->_collision);

	shovel->_shovel.imageName = "shovelBasic";
	shovel->_shovel.img = IMAGEMANAGER->findImage("shovelBasic");
}

void shovelBasic::exit(shovel * shovel)
{
}

