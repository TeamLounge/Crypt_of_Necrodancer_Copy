#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	SOUNDMANAGER->addSound("zone1-1", "music/zone1_1.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-1_shopkeeper", "music/zone1_1_shopkeeper.ogg", true, false);
	CAMERAMANAGER->setCamera(0, 0);

	//��
	_map = new mapGenerator;
	_map->init(70, 70);
	_map->generate(7);

	//�÷��̾�
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init();

	//���ʹ�
	_em = new enemyManager;
	_em->setMapGeneratorMemoryAddressLink(_map);
	_em->setPlayerMemoryAddressLink(_player);
	_em->init();

	//UI
	_UIM = new UIManager;
	_UIM->init("zone1-1", 355.0f);
	_UIM->setHeartBeat(4);
	_UIM->setHeart(5);
	_UIM->setItemHUD();
	_UIM->setMoney();
	_UIM->setMoneyNumber();

	//������Ʈ
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);
	_objectManager->setObjectEnemyManagerMemoryAddressLink(_em);
	_objectManager->getBomb()->setBombMapMemoryAddressLink(_map);

	//���� �÷���
	SOUNDMANAGER->play("zone1-1", 0.2f);
	SOUNDMANAGER->play("zone1-1_shopkeeper", 0.2f);
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

	_weapon->setUIMMemortAddressLink(_UIM);
	_UIM->setWeaponMemoryAddressLink(_weapon);
	_UIM->setPlayerMemoryAddressLink(_player);

	_shovel->setMGMemoryAddressLink(_map);

	_em->setWeaponMemoryAddressLink(_weapon);

	_player->setPlayerUIMemoryAddressLink(_UIM);
	_player->setEmMemoryAddressLink(_em);

	int bossRoom;
	for (int i = 0; i < _map->getRoom().size(); i++)
	{
		if (_map->getRoom()[i].roomState == ROOM_BOSS)
			bossRoom = i;
	}
	for (int y = 0; y < _map->getRoom()[bossRoom].y + _map->getRoom()[bossRoom].height; ++y)
	{
		for (int x = 0; x < _map->getRoom()[bossRoom].x + _map->getRoom()[bossRoom].width; ++x)
		{
			if (_map->getTileTerrain(x, y) == STAIR_BOSS)
			{
				stairBossX = x;
				stairBossY = y;
			}
		}
	}


	return S_OK;
}

void playerTestScene::release()
{
}

void playerTestScene::update()
{
	_map->update(_player->getTileX(), _player->getTileY());
	_player->update();
	_UIM->updateItemHUD();
	//RENDERMANAGER->update();
	_em->update();
	_UIM->updateHeartBeat();
	_UIM->plusItemHUD(BOMB);
	_UIM->updateHeart();

	_objectManager->update();
	_weapon->update();
	_shovel->update();

	_shopkeeper->update();
	_UIM->updateMoney();
	_UIM->updateMoneyNumber(0, false);
	if (!_em->getIsMiniBoss())
	{
		//����� �ذ��������
		_map->setTileTerrain(stairBossX, stairBossY, STAIR_NONE);
		if (_player->getTileX() == stairBossX && _player->getTileY() == stairBossY)
		{
			SOUNDMANAGER->stop("zone1-1");
			SOUNDMANAGER->stop("zone1-1_shopkeeper");
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

	_player->render();

	_UIM->renderItemHUD();

	//_UIM->renderHeartBeat();
	_UIM->renderHeart();
	_weapon->render();
	_shovel->render();

	_objectManager->render();			//���� ���� ��
	_player->getBomb()->render();		//���� ���� ��
	_UIM->renderMoney();
	_UIM->renderMoneyNumber();

	if (_UIM->getIsPlayerDead())
	{
		IMAGEMANAGER->render("������Ʈ1", getMemDC(), CAMERAMANAGER->getCameraCenterX() - 200, CAMERAMANAGER->getCameraBOTTOM() - 200);
		IMAGEMANAGER->render("������Ʈ2", getMemDC(), CAMERAMANAGER->getCameraCenterX() + 50, CAMERAMANAGER->getCameraBOTTOM() - 200);
	}
}
