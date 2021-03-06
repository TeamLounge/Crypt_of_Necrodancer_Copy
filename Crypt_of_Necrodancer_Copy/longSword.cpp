#include "stdafx.h"
#include "spear.h"
#include "longSword.h"
#include "broadSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"
#include "rapier.h"
#include "throwDagger.h"

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
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new spear();
		break;
	case MAP_BROADSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_player->setIsThrow(false);
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_LONGSWORD);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new rapier();
		break;
	}

	return nullptr;
}

void longSword::update(weapon * weapon)
{
	if (weapon->_effectDirection)
	{
		weapon->_effectDirection = false;
		weapon->_isEffectOn = true;
		if (weapon->_player->getDirection() == LEFT)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("longSword_LR");
			weapon->_weaponEffect.currentFrameY = 1;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left - TILESIZE - TILESIZE,
				weapon->_player->getTileRect().top + 20, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == RIGHT)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("longSword_LR");
			weapon->_weaponEffect.currentFrameY = 0;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + TILESIZE + 20,
				weapon->_player->getTileRect().top + 20, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == UP)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("longSword_TB");
			weapon->_weaponEffect.currentFrameY = 0;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + 20,
				weapon->_player->getTileRect().top - TILESIZE - TILESIZE, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == DOWN)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("longSword_TB");
			weapon->_weaponEffect.currentFrameY = 1;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + 20,
				weapon->_player->getTileRect().top + TILESIZE, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}
	}

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

	if (weapon->_isEffectOn)
	{
		elapsedTime += TIMEMANAGER->getElapsedTime();
		if (elapsedTime >= 0.045f)
		{
			elapsedTime -= 0.045f;

			if (weapon->_weaponEffect.currentFrameX == weapon->_weaponEffect.img->getMaxFrameX())
			{
				weapon->_weaponEffect.currentFrameX = 0;
				weapon->_isEffectOn = false;
			}

			else weapon->_weaponEffect.currentFrameX++;
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

	weapon->_weapon.isThrow = false;
	weapon->_isThrowRender = false;

	elapsedTime = 0.f;
	speed = 0.f;
}

void longSword::exit(weapon * weapon)
{
}
