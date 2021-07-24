#include "stdafx.h"
#include "shovel.h"
#include "player.h"
#include "shovelTitanium.h"
#include "shovelBasic.h"

shovelType * shovelTitanium::inputHandle(shovel * shovel)
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		return new shovelBasic();
	}

	return nullptr;
}

void shovelTitanium::update(shovel * shovel)
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

void shovelTitanium::enter(shovel * shovel)
{
	shovel->_vCollision.push_back(shovel->_collision);

	shovel->_shovel.imageName = "shovelTitanium";
	shovel->_shovel.img = IMAGEMANAGER->findImage("shovelTitanium");
}

void shovelTitanium::exit(shovel * shovel)
{
}

