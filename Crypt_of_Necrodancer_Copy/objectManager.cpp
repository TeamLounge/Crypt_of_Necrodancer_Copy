#include "stdafx.h"
#include "objectManager.h"
#include "UIManager.h"
#include "weapon.h"
#include "shovel.h"
#include "dagger.h"
#include "broadSword.h"
#include "longSword.h"
#include "spear.h"
#include "rapier.h"

HRESULT objectManager::init()
{
	_isMusicSpeedChanged = false;
	_elapsedSec = 0;

	_bomb = new bomb;
	_bomb->init();
	_playerBeforeX = _playerBeforeY = 0;

	bodyName = "bodyarmor_basic";
	torchName = "torch_basic_none";
	foodName = "food_none";

	UIMANAGER->addUI("body", bodyName.c_str(), 0, 0);
	UIMANAGER->addUI("torch", torchName.c_str(), 0, 0);
	UIMANAGER->addUI("food", foodName.c_str(), 0, 0);

	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	playerObjectCollison();
	playerItemCollision();
	if (_isMusicSpeedChanged)
	{
		_elapsedSec += TIMEMANAGER->getElapsedTime();
		if (_elapsedSec >= 10.0f)
		{
			_elapsedSec -= 10.0f;
			SOUNDMANAGER->setPitch();
			_isMusicSpeedChanged = false;
			_map->setTileObjectFrameX(_music.tileX, _music.tileY, 0);
			_UIM->setBeatSpeed(370.0f);
			_em->setEnemySpeed(1.0f);
		}
	}
	_bomb->update();

	if (_player->getTileX() != _playerBeforeX || _player->getTileY() != _playerBeforeY)
	{
		_playerBeforeX = _player->getTileX();
		_playerBeforeY = _player->getTileY();
	}

	if (bodyName == "bodyarmor_basic")
	{
		_UIM->minusItemHUD(BODY);
	}

	else
	{
		_UIM->plusItemHUD(BODY);
	}

	if (torchName == "torch_basic_none")
	{
		_UIM->minusItemHUD(TORCH);
	}

	else
	{
		_UIM->plusItemHUD(TORCH);
	}
	if (_player->getFoodName() == "food_none")
	{
		foodName = "food_none";
	}

	if (foodName == "food_none")
	{
		_UIM->minusItemHUD(ITEM);
	}
	else
	{
		_UIM->plusItemHUD(ITEM);
	}

	if (!_player->getIsMove())
	{
		for (vector<tagPushedObject>::iterator iter = _playerPushedObject.begin(); iter != _playerPushedObject.end();)
		{
			_map->setTileObjectFrameX(iter->tileX, iter->tileY, 0);
			iter = _playerPushedObject.erase(iter);
		}
	}
	

}

void objectManager::render()
{
	_bomb->render();
}

void objectManager::render(int tileX, int tileY)
{
	_bomb->render(tileX, tileY);
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
		if (!_map->getIsBombFired(_player->getTileX(), _player->getTileY()))
		{
			_bomb->fire(_player->getTileX(), _player->getTileY(), _map->getRect(_player->getTileX(), _player->getTileY()));
			_map->setIsBombFired(_player->getTileX(), _player->getTileY(), true);
			_map->setTileObjectFrameX(_player->getTileX(), _player->getTileY(), 1);
		}
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
		_map->setTileObject(_player->getTileX(), _player->getTileY(), OBJ_NONE);

		//?????? ???????? ????
		if (_map->getTileObject(_player->getTileX(), _player->getTileY() - 1) == OBJ_NONE && _map->getTileItem(_player->getTileX(), _player->getTileY() - 1) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX(), _player->getTileY() - 1, (MAP_ITEM)RND->getFromIntTo(1, 13));
		}
		//????
		else if (_map->getTileObject(_player->getTileX(), _player->getTileY() + 1) == OBJ_NONE && _map->getTileItem(_player->getTileX(), _player->getTileY() + 1) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX(), _player->getTileY() + 1, (MAP_ITEM)RND->getFromIntTo(1, 13));
		}
		//??
		else if (_map->getTileObject(_player->getTileX() - 1, _player->getTileY()) == OBJ_NONE && _map->getTileItem(_player->getTileX() - 1, _player->getTileY()) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX() - 1, _player->getTileY(), (MAP_ITEM)RND->getFromIntTo(1, 13));
		}
		//??
		else if (_map->getTileObject(_player->getTileX() + 1, _player->getTileY()) == OBJ_NONE && _map->getTileItem(_player->getTileX() + 1, _player->getTileY()) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX() + 1, _player->getTileY(), (MAP_ITEM)RND->getFromIntTo(1, 13));
		}
		break;
	case BLACK_ITEM_BOX:
		_map->setTileObject(_player->getTileX(), _player->getTileY(), OBJ_NONE);
		//?????? ???????? ????
		if (_map->getTileObject(_player->getTileX(), _player->getTileY() - 1) == OBJ_NONE && _map->getTileItem(_player->getTileX(), _player->getTileY() - 1) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX(), _player->getTileY() - 1, (MAP_ITEM)RND->getFromIntTo(7, 11));
		}
		//????
		else if (_map->getTileObject(_player->getTileX(), _player->getTileY() + 1) == OBJ_NONE && _map->getTileItem(_player->getTileX(), _player->getTileY() + 1) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX(), _player->getTileY() + 1, (MAP_ITEM)RND->getFromIntTo(7, 11));
		}
		//??
		else if (_map->getTileObject(_player->getTileX() - 1, _player->getTileY()) == OBJ_NONE && _map->getTileItem(_player->getTileX() - 1, _player->getTileY()) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX() - 1, _player->getTileY(), (MAP_ITEM)RND->getFromIntTo(7, 11));
		}
		//??
		else if (_map->getTileObject(_player->getTileX() + 1, _player->getTileY()) == OBJ_NONE && _map->getTileItem(_player->getTileX() + 1, _player->getTileY()) == MAP_ITEM_NONE)
		{
			_map->setTileItem(_player->getTileX() + 1, _player->getTileY(), (MAP_ITEM)RND->getFromIntTo(7, 11));
		}
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

void objectManager::playerItemCollision()
{
	if (_player->getTileX() == _playerBeforeX && _player->getTileY() == _playerBeforeY) return;
	int playerTileX = _player->getTileX();
	int playerTileY = _player->getTileY();
	switch (_map->getTileItem(playerTileX, playerTileY))
	{
	case MAP_ITEM_NONE:
		break;
	case MAP_TORCH_PLUS_1:
		if (_player->getVision()->getStartLightNum() == BASICVISION)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			torchName = "torch_basic_none";
		}
		else if (_player->getVision()->getStartLightNum() == BASICVISION + 1)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_TORCH_PLUS_1);
			torchName = "torch_plus_1";
		}
		else if (_player->getVision()->getStartLightNum() == BASICVISION + 2)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_TORCH_PLUS_2);
			torchName = "torch_plus_2";
		}
		_player->getVision()->setStartLightNum(BASICVISION + 1);
		torchName = "torch_plus_1";
		SOUNDMANAGER->play("pickup_general", 0.6f);
		break;
	case MAP_TORCH_PLUS_2:
		if (_player->getVision()->getStartLightNum() == BASICVISION)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			torchName = "torch_basic_none";
		}
		else if (_player->getVision()->getStartLightNum() == BASICVISION + 1)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_TORCH_PLUS_1);
			torchName = "torch_plus_1";
		}
		else if (_player->getVision()->getStartLightNum() == BASICVISION + 2)
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_TORCH_PLUS_2);
			torchName = "torch_plus_2";
		}
		_player->getVision()->setStartLightNum(BASICVISION + 2);
		torchName = "torch_plus_2";
		SOUNDMANAGER->play("pickup_general", 0.6f);
		break;
	case MAP_LEATHER_ARMOR:
		if (_player->getBodyImageName() == "player_body_basic")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			bodyName = "bodyarmor_basic";
		}
		else if (_player->getBodyImageName() == "player_body_leather")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_LEATHER_ARMOR);
			bodyName = "leather_armor";
		}
		else if (_player->getBodyImageName() == "player_body_chain")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_CHAIN_ARMOR);
			bodyName = "chain_armor";
		}
		_player->setBodyImageName("player_body_leather");
		bodyName = "leather_armor";
		SOUNDMANAGER->play("pickup_armor", 0.6f);
		break;
	case MAP_CHAIN_ARMOR:
		if (_player->getBodyImageName() == "player_body_basic")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			bodyName = "bodyarmor_basic";
		}
		else if (_player->getBodyImageName() == "player_body_leather")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_LEATHER_ARMOR);
			bodyName = "leather_armor";
		}
		else if (_player->getBodyImageName() == "player_body_chain")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_CHAIN_ARMOR);
			bodyName = "chain_armor";
		}
		_player->setBodyImageName("player_body_chain");
		bodyName = "chain_armor";

		SOUNDMANAGER->play("pickup_armor", 0.6f);
		break;
	case MAP_APPLE:
		if (foodName == "food_none")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			foodName = "food_none";
		}

		else if (foodName == "apple")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_APPLE);
			foodName = "apple";
		}

		else if(foodName == "cheese")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_CHEESE);
			foodName = "cheese";
		}

		foodName = "apple";
		_player->setFoodName("apple");
		SOUNDMANAGER->play("pickup_general", 0.6f);
		break;
	case MAP_CHEESE:
		if (foodName == "food_none")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
			foodName = "food_none";
		}

		else if (foodName == "apple")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_APPLE);
			foodName = "apple";
		}

		else if (foodName == "cheese")
		{
			_map->setTileItem(playerTileX, playerTileY, MAP_CHEESE);
			foodName = "cheese";
		}

		foodName = "cheese";
		_player->setFoodName("cheese");
		SOUNDMANAGER->play("pickup_general", 0.6f);
		break;
	case MAP_COIN1:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(1, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN2:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(2, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN3:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(3, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN4:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(4, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN5:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(5, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN6:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(6, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN7:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(7, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN8:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(8, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN9:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(9, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
		break;
	case MAP_COIN10:
		_map->setTileItem(playerTileX, playerTileY, MAP_ITEM_NONE);
		_UIM->updateMoneyNumber(10, false);
		SOUNDMANAGER->play("pickup_gold", 0.6f);
	default:
		break;
	}
}

void objectManager::playerMove(int addTileX, int addTileY, PLAYER_ENEMY_DIRECTION dir)
{
	tagPushedObject pushedObj;
	if (!_player->getIsMove() && !_player->getIsRush())
	{
		//???? ?????????? ????????tileY - 1?? ???????? ????
		OBJECT obj = _map->getTileObject(_player->getTileX() + addTileX, _player->getTileY() + addTileY);
		_map->setTileObjectFrameX(_player->getTileX(), _player->getTileY(), 1);
		if (obj != WALL_BASIC && obj != WALL_GOLD && obj != WALL_STONE && obj != WALL_CRACK && obj != WALL_DOOR && obj != WALL_END && !_map->getIsEnemy(_player->getTileX() + addTileX, _player->getTileY() + addTileY))
		{
			pushedObj.tileX = _player->getTileX();
			pushedObj.tileY = _player->getTileY();
			_playerPushedObject.emplace_back(pushedObj);
			_player->setDirection(dir);
			_player->setTileX(_player->getTileX() + addTileX);
			_player->setTileY(_player->getTileY() + addTileY);
			_player->setIsMove(true);
			SOUNDMANAGER->play("trap_bounce", 0.6f);
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
		if (speed == 1.2f)
		{
			_UIM->setBeatSpeed(444.0f);
			_em->setEnemySpeed(0.8f);
		}
		else if (speed == 0.8f)
		{
			_UIM->setBeatSpeed(296.0f);
			_em->setEnemySpeed(1.2f);
		}
	}
}
