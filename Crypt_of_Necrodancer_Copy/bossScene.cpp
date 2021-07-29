#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init()
{
	SOUNDMANAGER->addSound("boss", "music/boss_2.ogg", true, true);
	CAMERAMANAGER->setCamera(0, 0);

	//¸Ê
	_map = new mapGenerator;
	_map->init(BOSSMAPX, BOSSMAPY);
	_map->generateBossMap();

	//ÇÃ·¹ÀÌ¾î
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init();

	//¿¡³Ê¹Ì
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->bossRoomInit();

	//UI
	_UIM = new UIManager;
	_UIM->init("boss", 630.0f, 230);
	_UIM->setHeartBeat(3);
	_UIM->setHeart(5);
	_UIM->setItemHUD();
	_UIM->setMoney();
	_UIM->setMoneyNumber();
	_UIM->setDiamond();
	_UIM->setDiaNumber();

	//¿ÀºêÁ§Æ®
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);
	_objectManager->setObjectEnemyManagerMemoryAddressLink(_em);
	_objectManager->getBomb()->setBombMapMemoryAddressLink(_map);

	_weapon = new weapon;
	_weapon->init();

	_shovel = new shovel;
	_shovel->init();

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
	_weapon->setEMMemoryAddressLink(_em);

	_weapon->setUIMMemortAddressLink(_UIM);
	_UIM->setWeaponMemoryAddressLink(_weapon);
	_UIM->setPlayerMemoryAddressLink(_player);

	_shovel->setMGMemoryAddressLink(_map);

	_em->setWeaponMemoryAddressLink(_weapon);

	_player->setPlayerUIMemoryAddressLink(_UIM);
	_player->setEmMemoryAddressLink(_em);

	SOUNDMANAGER->play("boss", 0.4f);

	return S_OK;
}

void bossScene::release()
{
}

void bossScene::update()
{
	_map->update(_player->getTileX(), _player->getTileY());
	_player->update();
	_weapon->update();

	_em->bossRoomUpdate();

	_UIM->updateItemHUD();
	_UIM->updateHeartBeat();
	_UIM->plusItemHUD(BOMB);
	_UIM->updateHeart();
	_UIM->updateMoney();
	_UIM->updateMoneyNumber(0, false);
	_UIM->updateDiamond();
	_UIM->updateDiaNumber(0, false);

	_objectManager->update();
	_shovel->update();

	if (_player->getTileY() < 14)
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
			_em->bossRoomRender(j, i);
			_objectManager->render(j, i);
		}
	}

	_UIM->renderItemHUD();
	_UIM->renderHeart();

	_objectManager->render();			//Æø¹ß ÇßÀ» ¶§
	_player->getBomb()->render();		//Æø¹ß ÇßÀ» ¶§
	_UIM->renderMoney();
	_UIM->renderMoneyNumber();
	_UIM->renderDiamond();
	_UIM->renderDiaNumber();

	_weapon->render();
	_shovel->render();

	if (_UIM->getIsPlayerDead())
	{
		IMAGEMANAGER->render("Á×À½¸àÆ®1", getMemDC(), CAMERAMANAGER->getCameraCenterX() - 200, CAMERAMANAGER->getCameraBOTTOM() - 200);
		IMAGEMANAGER->render("Á×À½¸àÆ®2", getMemDC(), CAMERAMANAGER->getCameraCenterX() + 50, CAMERAMANAGER->getCameraBOTTOM() - 200);
	}
}