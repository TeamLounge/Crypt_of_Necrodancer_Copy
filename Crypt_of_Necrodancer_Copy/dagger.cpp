#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"
#include "rapier.h"
#include "UIManager.h"

weaponType * dagger::inputHandle(weapon* weapon)
{
	if (weapon->_player->getTileX() == weapon->_playerBeforeX && weapon->_player->getTileY() == weapon->_playerBeforeY) return nullptr;

	switch (weapon->_map->getTileItem(weapon->_player->getTileX(), weapon->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_SPEAR:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		return new spear();
		break;
	case MAP_BROADSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_player->setIsThrow(false);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		return new rapier();
		break;
	}

	return nullptr;
}

void dagger::update(weapon* weapon)
{
	if (weapon->_player->getDirection() == LEFT)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left -TILESIZE,
			weapon->_player->getTileRect().top,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX() - 1;
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY();
	}

	if (weapon->_player->getDirection() == UP)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top - TILESIZE,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX();
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY() - 1;
	}

	if (weapon->_player->getDirection() == RIGHT)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left + TILESIZE,
			weapon->_player->getTileRect().top,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX() + 1;
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY();
	}

	if (weapon->_player->getDirection() == DOWN)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top + TILESIZE,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX();
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY() + 1;
	}
}

void dagger::enter(weapon* weapon)
{
	weapon->_vCollision.push_back(weapon->_collision);

	weapon->_weapon.imageName = "dagger";
	weapon->_weapon.img = IMAGEMANAGER->findImage("dagger");
}

void dagger::exit(weapon* weapon)
{

}
