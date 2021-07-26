#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init()
{
	SOUNDMANAGER->addSound("boss", "music/boss_2.ogg", true, false);

	//맵
	_map = new mapGenerator;
	_map->init(BOSSMAPX, BOSSMAPY);
	_map->generateBossMap();

	//플레이어
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init();

	_weapon = new weapon;
	_weapon->init();


	_weapon->setPlayerMemoryAddressLink(_player);
	_player->setWeaponMemoryAddressLink(_weapon);

	_weapon->setMGMemoryAddressLink(_map);
	//오브젝트
	//_objectManager = new objectManager;
	//_objectManager->init();
	//_objectManager->setObjectMapMemoryAddressLink(_map);
	//_objectManager->setObjectPlayerMemoryAddressLink(_player);
	//_objectManager->getBomb()->setBombMapMemoryAddressLink(_map);

	SOUNDMANAGER->play("boss", 0.2f);

	return S_OK;
}

void bossScene::release()
{
}

void bossScene::update()
{
	_map->update(_player->getTileX(), _player->getTileY());
	_player->update();
	//_objectManager->update();
}

void bossScene::render()
{
	_map->render(_player->getTileX(), _player->getTileY(), true);
	for (int i = _player->getTileY() - VISIONY / 2; i <= _player->getTileY() + VISIONY / 2; i++)
	{
		if (i < 0) continue;
		if (i >= _map->getYSize()) break;
		for (int j = _player->getTileX() - VISIONX / 2; j < _player->getTileX() + VISIONX / 2; j++)
		{
			if (j < 0) continue;
			if (j >= _map->getXSize()) break;
			_map->render(j, i, false);
			_player->render(j, i);
			//_objectManager->render(j, i);
		}
	}
}
