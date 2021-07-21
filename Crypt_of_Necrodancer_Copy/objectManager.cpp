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
		playerMove(0, -1, UP);
		break;
	case TR_DOWN:
		playerMove(0, 1, DOWN);
		break;
	case TR_LEFT:
		playerMove(-1, 0, LEFT);
		break;
	case TR_RIGHT:
		playerMove(1, 0, RIGHT);
		break;
	case TR_FAST:
		break;
	case TR_SLOW:
		break;
	case TR_JUMP:
		switch (_player->getDirection())
		{
		case LEFT:
			playerMove(-1, 0, LEFT);
			break;
		case RIGHT:
			playerMove(1, 0, RIGHT);
			break;
		case UP:
			playerMove(0, -1, UP);
			break;
		case DOWN:
			playerMove(0, 1, DOWN);
			break;
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
			_map->setTileObjectFrameX(iter->tileX, iter->tileY, 0);
			iter = _playerPushedObject.erase(iter);
		}
	}
}

void objectManager::enemyObjectCollison()
{
}

void objectManager::playerMove(int addTileX, int addTileY, PLAYER_ENEMY_DIRECTION dir)
{
	tagPushedObject pushedObj;
	if (!_player->getIsMove())
	{
		//���� �����ϹǷ� �÷��̾�tileY - 1�� ������Ʈ ��
		OBJECT obj = _map->getTileObject(_player->getTileX() + addTileX, _player->getTileY() + addTileY);
		_map->setTileObjectFrameX(_player->getTileX(), _player->getTileY(), 1);
		if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END)
		{
			pushedObj.tileX = _player->getTileX();
			pushedObj.tileY = _player->getTileY();
			_playerPushedObject.emplace_back(pushedObj);

			_player->setDirection(dir);
			_player->setTileX(_player->getTileX() + addTileX);
			_player->setTileY(_player->getTileY() + addTileY);
			_player->setIsMove(true);
		}
	}
}
