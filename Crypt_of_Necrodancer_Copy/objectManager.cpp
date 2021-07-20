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
	tagPushedObject pushedObj;
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
			_map->setTileObject(_player->getTileX(), _player->getTileY(), TR_UP, 1, 0);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				pushedObj.tileX = _player->getTileX();
				pushedObj.tileY = _player->getTileY();
				pushedObj.obj = TR_UP;
				_playerPushedObject.emplace_back(pushedObj);

				_player->setDirection(UP);
				_player->setTileY(_player->getTileY() - 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_DOWN:
		if (!_player->getIsMove())
		{
			//밑으로 가야하므로 플레이어tileY + 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			_map->setTileObject(_player->getTileX(), _player->getTileY(), TR_DOWN, 1, 0);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				pushedObj.tileX = _player->getTileX();
				pushedObj.tileY = _player->getTileY();
				pushedObj.obj = _map->getTileObject(_player->getTileX(), _player->getTileY());
				_playerPushedObject.emplace_back(pushedObj);

				_player->setDirection(DOWN);
				_player->setTileY(_player->getTileY() + 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_LEFT:
		if (!_player->getIsMove())
		{
			//왼쪽으로 가야하므로 플레이어tileX - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			_map->setTileObject(_player->getTileX(), _player->getTileY(), TR_LEFT, 1, 0);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				pushedObj.tileX = _player->getTileX();
				pushedObj.tileY = _player->getTileY();
				pushedObj.obj = _map->getTileObject(_player->getTileX(), _player->getTileY());
				_playerPushedObject.emplace_back(pushedObj);

				_player->setDirection(LEFT);
				_player->setTileX(_player->getTileX() - 1);
				_player->setIsMove(true);
			}
		}
		break;
	case TR_RIGHT:
		if (!_player->getIsMove())
		{
			//오른쪽으로 가야하므로 플레이어tileX - 1의 오브젝트 비교
			OBJECT obj = _map->getTileObject(_player->getTileX(), _player->getTileY() - 1);
			_map->setTileObject(_player->getTileX(), _player->getTileY(), TR_RIGHT, 1, 0);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				pushedObj.tileX = _player->getTileX();
				pushedObj.tileY = _player->getTileY();
				pushedObj.obj = _map->getTileObject(_player->getTileX(), _player->getTileY());
				_playerPushedObject.emplace_back(pushedObj);

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
			_map->setTileObject(_player->getTileX(), _player->getTileY(), TR_JUMP, 1, 0);
			if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
			{
				pushedObj.tileX = _player->getTileX();
				pushedObj.tileY = _player->getTileY();
				pushedObj.obj = _map->getTileObject(_player->getTileX(), _player->getTileY());
				_playerPushedObject.emplace_back(pushedObj);

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

	if (!_player->getIsMove())
	{
		for (vector<tagPushedObject>::iterator iter = _playerPushedObject.begin(); iter!=_playerPushedObject.end();)
		{
			_map->setTileObject(iter->tileX, iter->tileY, iter->obj, 0, 0);
			iter = _playerPushedObject.erase(iter);
		}
	}
}

void objectManager::enemyObjectCollison()
{
}
