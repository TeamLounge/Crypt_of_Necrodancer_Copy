#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"

weaponType * dagger::inputHandle(weapon* weapon)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		return new broadSword;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		return new longSword;
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
	}

	if (weapon->_player->getDirection() == UP)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top - TILESIZE,
			TILESIZE, TILESIZE);
	}

	if (weapon->_player->getDirection() == RIGHT)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left + TILESIZE,
			weapon->_player->getTileRect().top,
			TILESIZE, TILESIZE);
	}

	if (weapon->_player->getDirection() == DOWN)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top + TILESIZE,
			TILESIZE, TILESIZE);
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
