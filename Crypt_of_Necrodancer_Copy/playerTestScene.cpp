#include "stdafx.h"
#include "playerTestScene.h"


HRESULT playerTestScene::init()
{
	SOUNDMANAGER->addSound("zone1-1", "music/zone1_1.ogg", true, false);
	SOUNDMANAGER->addSound("zone1-1_shopkeeper", "music/zone1_1_shopkeeper.ogg", true, false);
	
	//��
	_map = new mapGenerator;
	_map->init(70,70);
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
	_UIM->init();
	CAMERAMANAGER->setCamera(0, 0);
	_UIM->setHeartBeat(7);
	_UIM->setItemHUD();

	//������Ʈ
	_objectManager = new objectManager;
	_objectManager->init();
	_objectManager->setObjectMapMemoryAddressLink(_map);
	_objectManager->setObjectPlayerMemoryAddressLink(_player);
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
	_em->update();
	_UIM->updaetHeartBeat(3.0f);
	_objectManager->update();
	_weapon->update();
	_UIM->updateItemHUD();
	_shovel->update();

	_shopkeeper->update();

	_UIM->plusItemHUD(BOMB);

	if (_objectManager->getBodyName() == "bodyarmor_basic")
	{
		_UIM->minusItemHUD(BODY);
	}

	else
	{
		_UIM->plusItemHUD(BODY);
	}

	if (_objectManager->getTorchName() == "torch_basic_none")
	{
		_UIM->minusItemHUD(TORCH);
	}

	else
	{
		_UIM->plusItemHUD(TORCH);
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
			//_objectManager->render(j, i);
		}
	}
	_em->render();
	//_UIM->renderHeartBeat();
	//_weapon->render();
	//_UIM->renderItemHUD();
	//_shovel->render();

	//_objectManager->render();
	//_player->getBomb()->render();
}
