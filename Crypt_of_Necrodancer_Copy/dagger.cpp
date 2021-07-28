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
	//스로우가 아닐때
	if (!weapon->_player->getIsThrow())
	{
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
	}

	//스로우일때
	else
	{
		if (weapon->_player->getDirection() == LEFT)
		{
			for (int i = 0; i < weapon->_map->getXSize(); ++i)
			{
				(weapon->_vCollision.begin() + 0)->tileX = weapon->_throwTileX - i;
				(weapon->_vCollision.begin() + 0)->tileY = weapon->_throwTileY;

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY))
				{
					weapon->_player->setAttack(true);
				}

				else if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + 0)->tileX + 1,
						(weapon->_vCollision.begin() + 0)->tileY, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrow(false);
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == UP)
		{
			for (int i = 0; i < weapon->_map->getYSize(); ++i)
			{
				(weapon->_vCollision.begin() + 0)->tileX = weapon->_throwTileX;
				(weapon->_vCollision.begin() + 0)->tileY = weapon->_throwTileY - i;

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY))
				{
					weapon->_player->setAttack(true);
				}

				else if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + 0)->tileX,
						(weapon->_vCollision.begin() + 0)->tileY + 1, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrow(false);
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == RIGHT)
		{
			for (int i = 0; i < weapon->_map->getXSize(); ++i)
			{
				(weapon->_vCollision.begin() + 0)->tileX = weapon->_throwTileX + i;
				(weapon->_vCollision.begin() + 0)->tileY = weapon->_throwTileY;

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY))
				{
					weapon->_player->setAttack(true);
				}

				else if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + 0)->tileX - 1,
						(weapon->_vCollision.begin() + 0)->tileY, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrow(false);
					break;
				}
			}
		}

		if (weapon->_player->getDirection() == DOWN)
		{
			for (int i = 0; i < weapon->_map->getYSize(); ++i)
			{
				(weapon->_vCollision.begin() + 0)->tileX = weapon->_throwTileX;
				(weapon->_vCollision.begin() + 0)->tileY = weapon->_throwTileY + i;

				OBJECT obj = weapon->_map->getTileObject((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY);

				if (weapon->_map->getIsEnemy((weapon->_vCollision.begin() + 0)->tileX, (weapon->_vCollision.begin() + 0)->tileY))
				{
					weapon->_player->setAttack(true);
				}

				else if (obj == WALL_BASIC || obj == WALL_CRACK ||
					obj == WALL_DOOR || obj == WALL_END || obj == WALL_GOLD || obj == WALL_STONE)
				{
					weapon->_map->setTileItem((weapon->_vCollision.begin() + 0)->tileX,
						(weapon->_vCollision.begin() + 0)->tileY - 1, MAP_DAGGER);
					CAMERAMANAGER->vibrateScreen((weapon->_player->getShadowRect().left + weapon->_player->getShadowRect().right) / 2,
						(weapon->_player->getShadowRect().top + weapon->_player->getShadowRect().bottom) / 2, 30.0f);
					weapon->_player->setIsThrow(false);
					break;
				}
			}
		}
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
