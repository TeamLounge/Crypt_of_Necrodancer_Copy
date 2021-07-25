#include "stdafx.h"
#include "shopkeeper.h"

HRESULT shopkeeper::init(string songName, POINT shopkeeperXY)
{
	_songName = songName;
	_shopkeeper = shopkeeperXY;
	return S_OK;
}

void shopkeeper::release()
{
}

void shopkeeper::update()
{
	//플레이어와 shopkeeper 거리에 따른 음량 조절
	_distance = getDistance(_shopkeeper.x, _shopkeeper.y, _player->getTileX(), _player->getTileY());
	if (_distance <= 3.0f)
	{
		SOUNDMANAGER->setVolume(_songName, 0.2f);
	}
	else if (_distance <= 6.0f)
	{
		SOUNDMANAGER->setVolume(_songName, 0.15f);
	}
	else if (_distance <= 9.0f)
	{
		SOUNDMANAGER->setVolume(_songName, 0.1f);
	}
	else if (_distance <= 12.0f)
	{
		SOUNDMANAGER->setVolume(_songName, 0.05f);
	}
	else
	{
		SOUNDMANAGER->setVolume(_songName, 0.0f);
	}

	_elapsedTime += TIMEMANAGER->getElapsedTime();
	if (_elapsedTime >= 0.2f)
	{
		_elapsedTime -= 0.2f;
		if (IMAGEMANAGER->findImage("shopkeeper")->getFrameX() >= 3)
		{
			IMAGEMANAGER->findImage("shopkeeper")->setFrameX(0);
			IMAGEMANAGER->findImage("shopkeeper_dark")->setFrameX(0);
		}
		else
		{
			IMAGEMANAGER->findImage("shopkeeper")->setFrameX(IMAGEMANAGER->findImage("shopkeeper")->getFrameX() + 1);
			IMAGEMANAGER->findImage("shopkeeper_dark")->setFrameX(IMAGEMANAGER->findImage("shopkeeper_dark")->getFrameX() + 1);
		}
	}
}

void shopkeeper::render()
{
}
