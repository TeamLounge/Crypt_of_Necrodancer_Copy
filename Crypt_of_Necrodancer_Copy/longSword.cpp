#include "stdafx.h"
#include "spear.h"
#include "longSword.h"
#include "broadSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"
#include "rapier.h"

weaponType * longSword::inputHandle(weapon * weapon)
{
	if (weapon->_player->getTileX() == weapon->_playerBeforeX && weapon->_player->getTileY() == weapon->_playerBeforeY) return nullptr;

	switch (weapon->_map->getTileItem(weapon->_player->getTileX(), weapon->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_SPEAR:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		return new spear();
		break;
	case MAP_BROADSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_player->setIsThrow(false);
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		return new rapier();
		break;
	}

	return nullptr;
}

void longSword::update(weapon * weapon)
{
	if (weapon->_player->getDirection() == LEFT)
	{
		for (int i = 0; i < 2; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left - TILESIZE - i * TILESIZE,
				weapon->_player->getTileRect().top,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() - 1 - i;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY();
		}
	}

	if (weapon->_player->getDirection() == UP)
	{
		for (int i = 0; i < 2; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left,
				weapon->_player->getTileRect().top - TILESIZE - i * TILESIZE,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX();
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() - 1 - i;
		}
	}

	if (weapon->_player->getDirection() == RIGHT)
	{
		for (int i = 0; i < 2; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left + TILESIZE + i * TILESIZE,
				weapon->_player->getTileRect().top,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() + 1 + i;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY();
		}
	}

	if (weapon->_player->getDirection() == DOWN)
	{
		for (int i = 0; i < 2; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left,
				weapon->_player->getTileRect().top + TILESIZE + i * TILESIZE,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX();
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() + 1 + i;
		}
	}
}

void longSword::enter(weapon * weapon)
{
	for (int i = 0; i < 2; ++i)
	{
		weapon->_vCollision.push_back(weapon->_collision);
	}

	weapon->_weapon.imageName = "longSword";
	weapon->_weapon.img = IMAGEMANAGER->findImage("longSword");
}

void longSword::exit(weapon * weapon)
{
}
