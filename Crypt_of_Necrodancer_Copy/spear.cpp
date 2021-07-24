#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"

weaponType * spear::inputHandle(weapon * weapon)
{
	return nullptr;
}

void spear::update(weapon * weapon)
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

void spear::enter(weapon * weapon)
{
	for (int i = 0; i < 2; ++i)
	{
		weapon->_vCollision.push_back(weapon->_collision);
	}

	weapon->_weapon.imageName = "spear";
	weapon->_weapon.img = IMAGEMANAGER->findImage("spear");
}

void spear::exit(weapon * weapon)
{
}
