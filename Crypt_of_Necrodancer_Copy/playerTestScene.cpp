#include "stdafx.h"
#include "playerTestScene.h"


HRESULT playerTestScene::init()
{
	SOUNDMANAGER->addSound("zone1-1", "music/zone1_1.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-1_shopkeeper", "music/zone1_1_shopkeeper.ogg", true, false);
	
	//맵
	_map = new mapGenerator;
	_map->init(70,70);
	_map->generate(7);

	//플레이어
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init(_map->getStartRoomX() + 2, _map->getStartRoomY() + 2);

	_player->setupPlayerRect();

	//에너미
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->init();

	//UI
	_UIM = new UIManager;
	_UIM->init();
	CAMERAMANAGER->setCamera(0, 0);
	_UIM->setHeartBeat(7);
	_UIM->setItemHUD();

	//오브젝트
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);

	//사운드 플레이
	SOUNDMANAGER->play("zone1-1", 0.5f);
	SOUNDMANAGER->play("zone1-1_shopkeeper", 0.5f);
	SOUNDMANAGER->setGroup("zone1-1");
	SOUNDMANAGER->setGroup("zone1-1_shopkeeper");

	_weapon = new weapon;
	_weapon->init();

	_weapon->setPlayerMemoryAddressLink(_player);
	_player->setWeaponMemoryAddressLink(_weapon);
	_weapon->setUIMMemortAddressLink(_UIM);
	_UIM->setWeaponMemoryAddressLink(_weapon);
	return S_OK;
}

void playerTestScene::release()
{
}

void playerTestScene::update()
{
	_map->update();
	_player->update();
	//RENDERMANAGER->update();
	_em->update();
	_UIM->updaetHeartBeat(3.0f);
	_objectManager->update();
	_weapon->update();
	_UIM->updateItemHUD();
}

void playerTestScene::render()
{
	_map->render();
	//_player->render();
	for (int i = 0; i < _map->getYSize(); i++)
	{
		for (int j = 0; j < _map->getXSize(); j++)
		{
			_map->render(j, i);
			_player->render(j, i);
		}
	}
	_em->render();
	_UIM->renderHeartBeat();
	_weapon->render();
	_UIM->renderItemHUD();

	_objectManager->render();
}
