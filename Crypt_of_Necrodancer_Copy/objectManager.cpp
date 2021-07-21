#include "stdafx.h"
#include "objectManager.h"

HRESULT objectManager::init()
{
	_isMusicSpeedChanged = false;
	_elapsedSec = 0;
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	playerObjectCollison();
	if (_isMusicSpeedChanged)
	{
		_elapsedSec += TIMEMANAGER->getElapsedTime();
		if (_elapsedSec >= 15.0f)
		{
			_elapsedSec -= 15.0f;
			SOUNDMANAGER->setPitch();
			_isMusicSpeedChanged = false;
			_map->setTileObjectFrameX(_music.tileX, _music.tileY, 0);
		}
	}
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
		changeMusicSpeed(1.2f);
		break;
	case TR_SLOW:
		changeMusicSpeed(0.8f);
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
		//위로 가야하므로 플레이어tileY - 1의 오브젝트 비교
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

void objectManager::changeMusicSpeed(float speed)
{
	if (!_isMusicSpeedChanged)
	{
		SOUNDMANAGER->setPitch(speed);
		_isMusicSpeedChanged = true;
		_map->setTileObjectFrameX(_player->getTileX(), _player->getTileY(), 1);
		_music.tileX = _player->getTileX();
		_music.tileY = _player->getTileY();
	}
}
