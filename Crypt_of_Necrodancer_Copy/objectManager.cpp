#include "stdafx.h"
#include "objectManager.h"

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	playerObjectCollison();
}

void objectManager::render()
{
}

void objectManager::playerObjectCollison()
{
	switch (_map->getTileObject(_player->getTileX(), _player->getTileY()))
	{
	case OBJ_NONE:
		break;
	case WALL_BASIC:
		break;
	case WALL_GOLD:
		break;
	case WALL_STONE:
		break;
	case WALL_CRACK:
		break;
	case WALL_DOOR:
		break;
	case WALL_END:
		break;
	case TR_BOMB:
		break;
	case TR_UP:
		if (!_player->getIsMove())
		{
			//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				_player->setDirection(UP);
				_player->setTileY(_player->getTileY() - 1);
				_player->setIsMove(true);
			}
		}

		break;
	case TR_DOWN:
		if (!_player->getIsMove())
		{
			//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				_player->setDirection(DOWN);
				_player->setTileY(_player->getTileY() + 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_LEFT:
		if (!_player->getIsMove())
		{
			//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				_player->setDirection(LEFT);
				_player->setTileX(_player->getTileX() - 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_RIGHT:
		if (!_player->getIsMove())
		{
			//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				_player->setDirection(RIGHT);
				_player->setTileX(_player->getTileX() + 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_FAST:
		break;
	case TR_SLOW:
		break;
	case TR_JUMP:
		if (!_player->getIsMove())
		{
			//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				switch (_player->getDirection())
				{
				case LEFT:
					_player->setTileX(_player->getTileX() - 1);
					_player->setIsMove(true);
					break;
				case RIGHT:
					_player->setTileX(_player->getTileX() + 1);
					_player->setIsMove(true);
					break;
				case UP:
					_player->setTileY(_player->getTileY() - 1);
					_player->setIsMove(true);
					break;
				case DOWN:
					_player->setTileY(_player->getTileY() + 1);
					_player->setIsMove(true);
					break;
				}
			}
		}
		break;
	case TR_DOOR:
		break;
	case TR_SPIKE:
		break;
	case RED_ITEM_BOX:
		break;
	case BLACK_ITEM_BOX:
		break;
	case BOX:
		break;
	case BARREL:
		break;
	}
}

void objectManager::enemyObjectCollison()
{
}
