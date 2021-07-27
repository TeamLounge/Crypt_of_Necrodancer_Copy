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

	if (shovel->_player->getTileX() == shovel->_playerBeforeX && shovel->_player->getTileY() == shovel->_playerBeforeY) return nullptr;

	switch (shovel->_map->getTileItem(shovel->_player->getTileX(), shovel->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_TITANUM_SHOVEL:
		shovel->_map->setTileItem(shovel->_player->getTileX(), shovel->_player->getTileY(), MAP_ITEM_NONE);
		return new shovelTitanium();
		break;
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

		(shovel->_vCollision.begin() + 0)->tileX = shovel->_player->getTileX() - 1;
		(shovel->_vCollision.begin() + 0)->tileY = shovel->_player->getTileY();
	}

	if (shovel->_player->getDirection() == UP)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left,
			shovel->_player->getTileRect().top - TILESIZE,
			TILESIZE, TILESIZE);

		(shovel->_vCollision.begin() + 0)->tileX = shovel->_player->getTileX();
		(shovel->_vCollision.begin() + 0)->tileY = shovel->_player->getTileY() - 1;
	}

	if (shovel->_player->getDirection() == RIGHT)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left + TILESIZE,
			shovel->_player->getTileRect().top,
			TILESIZE, TILESIZE);
		(shovel->_vCollision.begin() + 0)->tileX = shovel->_player->getTileX() + 1;
		(shovel->_vCollision.begin() + 0)->tileY = shovel->_player->getTileY();
	}

	if (shovel->_player->getDirection() == DOWN)
	{
		(shovel->_vCollision.begin() + 0)->rc = RectMake(
			shovel->_player->getTileRect().left,
			shovel->_player->getTileRect().top + TILESIZE,
			TILESIZE, TILESIZE);
		(shovel->_vCollision.begin() + 0)->tileX = shovel->_player->getTileX();
		(shovel->_vCollision.begin() + 0)->tileY = shovel->_player->getTileY() + 1;
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

