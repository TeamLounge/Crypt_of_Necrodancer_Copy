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

	//에너미
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->bossRoomInit();

	//오브젝트
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);
	_objectManager->getBomb()->setBombMapMemoryAddressLink(_map);

	_weapon = new weapon;
	_weapon->init();

	_shovel = new shovel;
	_shovel->init();

	//UI
	_UIM = new UIManager;
	_UIM->init("boss", 200.0f);
	CAMERAMANAGER->setCamera(0, 0);
	_UIM->setHeartBeat(7);
	_UIM->setItemHUD();

	_weapon->setPlayerMemoryAddressLink(_player);
	_player->setWeaponMemoryAddressLink(_weapon);
	_shovel->setPlayerMemoryAddressLink(_player);
	_player->setShovelMemoryAddressLink(_shovel);

	_objectManager->setUIMMemoryAddressLink(_UIM);
	_UIM->setOMMemoryAddressLink(_objectManager);
	_shovel->setOMMemoryAddressLink(_objectManager);
	_weapon->setOMMemoryAddressLink(_objectManager);
	_objectManager->setWeaponMemoryAddressLink(_weapon);
	_objectManager->setShovelMemoryAddressLink(_shovel);
	_weapon->setMGMemoryAddressLink(_map);
	_player->setPlayerUIMemoryAddressLink(_UIM);
	_em->setWeaponMemoryAddressLink(_weapon);
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

	_em->bossRoomUpdate();
	_UIM->updateHeartBeat();
	_objectManager->update();
	_weapon->update();
	_shovel->update();

	_UIM->plusItemHUD(BOMB);
	_UIM->updateItemHUD();

	if (_player->getTileY() < 15)
	{
		_map->setTileObject(5, 15, WALL_END, 4, 3);
		_map->setTileObject(6, 15, WALL_END, 4, 3);
		_map->setTileObject(7, 15, WALL_END, 4, 3);

	}

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
			_objectManager->render(j, i);
		}
	}
	_em->bossRoomRender();
	_UIM->renderHeartBeat();
	_weapon->render();
	_shovel->render();

	_objectManager->render();
	_player->getBomb()->render();

	_UIM->renderItemHUD();
	char str[124];
	sprintf_s(str, "%d, %d", _player->getTileX(), _player->getTileY());
	TextOut(getMemDC(), _player->getTileRect().left, _player->getTileRect().top, str, strlen(str));

	sprintf_s(str, "dir : %d", _player->getDirection());
	TextOut(getMemDC(), _player->getTileRect().left, _player->getTileRect().top, str, strlen(str));

}