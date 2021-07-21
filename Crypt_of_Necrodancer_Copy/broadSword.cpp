#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"

weaponType * broadSword::inputHandle(weapon * weapon)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		return new dagger();
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		return new longSword;
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
