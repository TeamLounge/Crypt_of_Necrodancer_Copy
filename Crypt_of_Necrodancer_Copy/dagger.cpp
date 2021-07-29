#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"
#include "rapier.h"
#include "UIManager.h"
#include "throwDagger.h"
#include "enemyManager.h"
#include "throwDagger.h"

weaponType * dagger::inputHandle(weapon* weapon)
{
	if (weapon->_player->getIsThrow())
	{
		return new throwDagger();
	}

	if (weapon->_player->getTileX() == weapon->_playerBeforeX && weapon->_player->getTileY() == weapon->_playerBeforeY) return nullptr;

	switch (weapon->_map->getTileItem(weapon->_player->getTileX(), weapon->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_SPEAR:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new spear();
		break;
	case MAP_BROADSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_player->setIsThrow(false);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_DAGGER);
		weapon->_UIM->minusItemHUD(THROW);
		SOUNDMANAGER->play("pickup_weapon", 0.6f);
		return new rapier();
		break;
	}

	return nullptr;
}

void dagger::update(weapon* weapon)
{
	if (weapon->_effectDirection)
	{
		weapon->_effectDirection = false;
		weapon->_isEffectOn = true;
		if (weapon->_player->getDirection() == LEFT)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("dagger_LR");
			weapon->_weaponEffect.currentFrameY = 1;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left - TILESIZE,
				weapon->_player->getTileRect().top + 20, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == RIGHT)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("dagger_LR");
			weapon->_weaponEffect.currentFrameY = 0;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + TILESIZE + 20,
				weapon->_player->getTileRect().top + 20, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == UP)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("dagger_TB");
			weapon->_weaponEffect.currentFrameY = 0;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + 20,
				weapon->_player->getTileRect().top - TILESIZE, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}

		if (weapon->_player->getDirection() == DOWN)
		{
			weapon->_weaponEffect.img = IMAGEMANAGER->findImage("dagger_TB");
			weapon->_weaponEffect.currentFrameY = 1;

			weapon->_weaponEffect.rc = RectMake(weapon->_player->getTileRect().left + 20,
				weapon->_player->getTileRect().top + TILESIZE, weapon->_weaponEffect.img->getFrameWidth(),
				weapon->_weaponEffect.img->getFrameHeight());
		}
	}

	if (weapon->_player->getDirection() == LEFT)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left -TILESIZE,
			weapon->_player->getTileRect().top,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX() - 1;
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY();

		weapon->_throwTileX = weapon->_player->getTileX();
		weapon->_throwTileY = weapon->_player->getTileY();
	}

	if (weapon->_player->getDirection() == UP)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top - TILESIZE,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX();
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY() - 1;

		weapon->_throwTileX = weapon->_player->getTileX();
		weapon->_throwTileY = weapon->_player->getTileY();
	}

	if (weapon->_player->getDirection() == RIGHT)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left + TILESIZE,
			weapon->_player->getTileRect().top,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX() + 1;
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY();

		weapon->_throwTileX = weapon->_player->getTileX();
		weapon->_throwTileY = weapon->_player->getTileY();
	}

	if (weapon->_player->getDirection() == DOWN)
	{
		(weapon->_vCollision.begin() + 0)->rc = RectMake(
			weapon->_player->getTileRect().left,
			weapon->_player->getTileRect().top + TILESIZE,
			TILESIZE, TILESIZE);

		(weapon->_vCollision.begin() + 0)->tileX = weapon->_player->getTileX();
		(weapon->_vCollision.begin() + 0)->tileY = weapon->_player->getTileY() + 1;

		weapon->_throwTileX = weapon->_player->getTileX();
		weapon->_throwTileY = weapon->_player->getTileY();
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

void dagger::enter(weapon* weapon)
{
	weapon->_vCollision.push_back(weapon->_collision);

	weapon->_weapon.imageName = "dagger";
	weapon->_weapon.img = IMAGEMANAGER->findImage("dagger");

	weapon->_weapon.isThrow = true;
	weapon->_isThrowRender = false;

	elapsedTime = 0.f;
	speed = 0.f;
}

void dagger::exit(weapon* weapon)
{

}
