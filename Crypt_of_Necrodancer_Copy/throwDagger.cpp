#include "stdafx.h"
#include "spear.h"
#include "broadSword.h"
#include "longSword.h"
#include "dagger.h"
#include "weapon.h"
#include "player.h"
#include "rapier.h"
#include "throwDagger.h"

weaponType * throwDagger::inputHandle(weapon * weapon)
{
	if (weapon->_player->getTileX() == weapon->_playerBeforeX && weapon->_player->getTileY() == weapon->_playerBeforeY) return nullptr;

	switch (weapon->_map->getTileItem(weapon->_player->getTileX(), weapon->_player->getTileY()))
	{
	case MAP_ITEM_NONE:
		return nullptr;
		break;
	case MAP_SPEAR:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_ITEM_NONE);
		return new spear();
		break;
	case MAP_BROADSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_ITEM_NONE);
		return new broadSword();
		break;
	case MAP_DAGGER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_ITEM_NONE);
		return new dagger();
		break;
	case MAP_LONGSWORD:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_ITEM_NONE);
		return new longSword();
		break;
	case MAP_RAPIER:
		weapon->_map->setTileItem(weapon->_player->getTileX(), weapon->_player->getTileY(), MAP_ITEM_NONE);
		return new rapier();
		break;
	}

	return nullptr;
}

void throwDagger::update(weapon * weapon)
{
	if (weapon->_player->getIsThrowReady())
	{
		if (weapon->_player->getDirection() == LEFT)
		{
			for (int i = 0; i < weapon->_vCollision.size(); ++i)
			{
				(weapon->_vCollision.begin() + i)->tileX = weapon->_throwTileX - i;
				(weapon->_vCollision.begin() + i)->tileY = weapon->_throwTileY;

				(weapon->_vCollision.begin() + i)->rc = RectMake(
					(weapon->_vCollision.begin() + i)->tileX * TILESIZE,
					(weapon->_vCollision.begin() + i)->tileY * TILESIZE,
					TILESIZE, TILESIZE);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY))
				{
					weapon->_player->setAttack(true);
					break;
				}

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY);

				if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + i)->tileX + 1,
						(weapon->_vCollision.begin() + i)->tileY, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrowReady(false);
					weapon->_UIM->minusItemHUD(PRESS);
					weapon->_UIM->minusItemHUD(THROW);
					weapon->_player->setIsThrow(false);
					weapon->_isEffectOn = false;
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == UP)
		{
			for (int i = 0; i < weapon->_vCollision.size(); ++i)
			{
				(weapon->_vCollision.begin() + i)->tileX = weapon->_throwTileX;
				(weapon->_vCollision.begin() + i)->tileY = weapon->_throwTileY - i;

				(weapon->_vCollision.begin() + i)->rc = RectMake(
					(weapon->_vCollision.begin() + i)->tileX * TILESIZE,
					(weapon->_vCollision.begin() + i)->tileY * TILESIZE,
					TILESIZE, TILESIZE);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY))
				{
					weapon->_player->setAttack(true);
					break;
				}

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY);

				if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + i)->tileX,
						(weapon->_vCollision.begin() + i)->tileY + 1, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrowReady(false);
					weapon->_UIM->minusItemHUD(PRESS);
					weapon->_UIM->minusItemHUD(THROW);
					weapon->_player->setIsThrow(false);
					weapon->_isEffectOn = false;
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == RIGHT)
		{
			for (int i = 0; i < weapon->_vCollision.size(); ++i)
			{
				(weapon->_vCollision.begin() + i)->tileX = weapon->_throwTileX + i;
				(weapon->_vCollision.begin() + i)->tileY = weapon->_throwTileY;

				(weapon->_vCollision.begin() + i)->rc = RectMake(
					(weapon->_vCollision.begin() + i)->tileX * TILESIZE,
					(weapon->_vCollision.begin() + i)->tileY * TILESIZE,
					TILESIZE, TILESIZE);


				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY))
				{
					weapon->_player->setAttack(true);
					break;
				}

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY);

				if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + i)->tileX - 1,
						(weapon->_vCollision.begin() + i)->tileY, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrowReady(false);
					weapon->_UIM->minusItemHUD(PRESS);
					weapon->_UIM->minusItemHUD(THROW);
					weapon->_player->setIsThrow(false);
					weapon->_isEffectOn = false;
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == DOWN)
		{
			for (int i = 0; i < weapon->_vCollision.size(); ++i)
			{
				(weapon->_vCollision.begin() + i)->tileX = weapon->_throwTileX;
				(weapon->_vCollision.begin() + i)->tileY = weapon->_throwTileY + i;

				(weapon->_vCollision.begin() + i)->rc = RectMake(
					(weapon->_vCollision.begin() + i)->tileX * TILESIZE,
					(weapon->_vCollision.begin() + i)->tileY * TILESIZE,
					TILESIZE, TILESIZE);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY))
				{
					weapon->_player->setAttack(true);
					break;
				}

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + i)->tileX, (weapon->_vCollision.begin() + i)->tileY);

				if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + i)->tileX,
						(weapon->_vCollision.begin() + i)->tileY - 1, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrowReady(false);
					weapon->_UIM->minusItemHUD(PRESS);
					weapon->_UIM->minusItemHUD(THROW);
					weapon->_player->setIsThrow(false);
					weapon->_isEffectOn = false;
					break;
				}
			}
		}
	}

	if (!weapon->_player->getIsThrowReady())
	{
		weapon->deleteCollision();
	}
}

void throwDagger::enter(weapon * weapon)
{
	for (int i = 0; i < TILESIZE; ++i)
	{
		weapon->_vCollision.push_back(weapon->_collision);
		weapon->_vWeaponEffect.push_back(weapon->_weaponEffect);
	}

	weapon->_weapon.imageName = "dagger";

	weapon->_weapon.isThrow = false;
	weapon->_isThrowRender = true;
	weapon->_effectDirection = true;

	elapsedTime = 0.f;
	speed = 0.f;
}

void throwDagger::exit(weapon * weapon)
{

}
