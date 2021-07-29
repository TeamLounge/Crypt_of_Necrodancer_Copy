#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	SOUNDMANAGER->addSound("zone1-1", "music/zone1_1.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-1_shopkeeper", "music/zone1_1_shopkeeper.ogg", true, false);
	CAMERAMANAGER->setCamera(0, 0);

	//¸Ê
	_map = new mapGenerator;
	_map->init(70, 70);
	_map->generate(7);

	//ÇÃ·¹ÀÌ¾î
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init();

	//¿¡³Ê¹Ì
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->init();

	//UI
	_UIM = new UIManager;
	_UIM->init("zone1-1", 355.0f, 100);
	_UIM->setHeartBeat(4);
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

	//»ç¿îµå ÇÃ·¹ÀÌ
	SOUNDMANAGER->play("zone1-1", 0.4f);
	SOUNDMANAGER->play("zone1-1_shopkeeper", 0.4f);
	SOUNDMANAGER->setGroup("zone1-1");
	SOUNDMANAGER->setGroup("zone1-1_shopkeeper");
	_weapon = new weapon;
	_weapon->init();

	_shovel = new shovel;
	_shovel->init();

	_weapon->setPlayerMemoryAddressLink(_player);
	_player->setWeaponMemoryAddressLink(_weapon);
	_shovel->setPlayerMemoryAddressLink(_player);
	_player->setShovelMemoryAddressLink(_shovel);

	_shopkeeper = new shopkeeper;
	_shopkeeper->init("zone1-1_shopkeeper", _map->getShopKeeperXY());
	_shopkeeper->setShopkeeperPlayerMemoryAddressLink(_player);

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

	stairBossX = _map->getBossStairX();
	stairBossY = _map->getBossStairY();

	return S_OK;
}

void playerTestScene::release()
{
	
}

void playerTestScene::update()
{
	_map->update(_player->getTileX(), _player->getTileY());
	_player->update();
	
	//RENDERMANAGER->update();
	_weapon->update();
	_em->update();
	
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

	_shopkeeper->update();

	if (!_em->getIsMiniBoss())
	{
		//¿©±â¸é ÇØ°ñ¹þ°ÜÁö°í
		_map->setTileTerrain(stairBossX, stairBossY, STAIR_NONE);
		if (_player->getTileX() == stairBossX && _player->getTileY() == stairBossY)
		{
			SOUNDMANAGER->stop("zone1-1");
			SOUNDMANAGER->stop("zone1-1_shopkeeper");
			UIMANAGER->deleteAll();
			SCENEMANAGER->changeScene("bossScene");
		}
	}
}

void playerTestScene::render()
{
	_map->render(_player->getTileX(), _player->getTileY(), true);
	for (int i = _player->getTileY() - VISIONY/2; i <= _player->getTileY() + VISIONY / 2; i++)
	{
		if (i < 0) continue;
		if (i >= _map->getYSize()) break;
		for (int j = _player->getTileX() - VISIONX / 2; j < _player->getTileX() + VISIONX / 2; j++)
		{
			if (j < 0) continue;
			if (j >= _map->getXSize()) break;
			_map->render(j, i, false);
			_player->render(j, i);
			_player->renderShovelEffect(j, i);
			_objectManager->render(j, i);
			_em->render(j, i);
		}
	}
	//_em->render();

	_UIM->renderItemHUD();
	_UIM->renderHeart();
	_weapon->render();
	_shovel->render();

	_objectManager->render();			//Æø¹ß ÇßÀ» ¶§
	_player->getBomb()->render();		//Æø¹ß ÇßÀ» ¶§
	_UIM->renderMoney();
	_UIM->renderMoneyNumber();
	_UIM->renderDiamond();
	_UIM->renderDiaNumber();	

	if (_UIM->getIsPlayerDead())
	{
		IMAGEMANAGER->render("Á×À½¸àÆ®1", getMemDC(), CAMERAMANAGER->getCameraCenterX() - 200, CAMERAMANAGER->getCameraBOTTOM() - 200);
		IMAGEMANAGER->render("Á×À½¸àÆ®2", getMemDC(), CAMERAMANAGER->getCameraCenterX() + 50, CAMERAMANAGER->getCameraBOTTOM() - 200);
	}
}
