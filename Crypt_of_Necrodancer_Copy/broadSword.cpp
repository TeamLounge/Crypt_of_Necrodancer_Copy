#include "stdafx.h"
#include "rapier.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"

weaponType * broadSword::inputHandle(weapon * weapon)
{
	if (weapon->_player->getTileX() == weapon->_playerBeforeX && weapon->_player->getTileY() == weapon->_playerBeforeY) return nullptr;

	switch (weapon->_map->getTileItem(weapon->_player->getTileX(), weapon->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_SPEAR:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_BROADSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new spear();
		break;
	case MAP_BROADSWORD:
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_player->setIsThrow(false);
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_BROADSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_BROADSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_BROADSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new rapier();
		break;
	}

	return nullptr;
}

void broadSword::update(weapon * weapon)
{
	if (weapon->_player->getDirection() == LEFT)
	{
		for (int i = 0; i < 3; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left - TILESIZE,
				weapon->_player->getTileRect().top - TILESIZE + i * TILESIZE,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() - 1;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() - 1 + i;
		}
	}

	if (weapon->_player->getDirection() == UP)
	{
		for (int i = 0; i < 3; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left - TILESIZE + i * TILESIZE,
				weapon->_player->getTileRect().top - TILESIZE,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() - 1 + i;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() - 1;
		}
	}

	if (weapon->_player->getDirection() == RIGHT)
	{
		for (int i = 0; i < 3; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left + TILESIZE,
				weapon->_player->getTileRect().top - TILESIZE + i * TILESIZE,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() + 1;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() - 1 + i;
		}
	}

	if (weapon->_player->getDirection() == DOWN)
	{
		for (int i = 0; i < 3; ++i)
		{
			(weapon->_vCollision.begin() + i)->rc = RectMake(
				weapon->_player->getTileRect().left - TILESIZE + i * TILESIZE,
				weapon->_player->getTileRect().top + TILESIZE ,
				TILESIZE, TILESIZE);

			(weapon->_vCollision.begin() + i)->tileX = weapon->_player->getTileX() - 1 + i;
			(weapon->_vCollision.begin() + i)->tileY = weapon->_player->getTileY() + 1;
		}
	}
}

void broadSword::enter(weapon * weapon)
{
	for (int i = 0; i < 3; ++i)
	{
		weapon->_vCollision.push_back(weapon->_collision);
	}

	weapon->_weapon.imageName = "broadSword";
	weapon->_weapon.img = IMAGEMANAGER->findImage("broadSword");
}

void broadSword::exit(weapon * weapon)
{

}
