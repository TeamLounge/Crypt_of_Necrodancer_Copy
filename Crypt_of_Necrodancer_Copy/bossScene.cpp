#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init()
{
	SOUNDMANAGER->addSound("boss", "music/boss_2.ogg", true, false);

	//¸Ê
	_map = new mapGenerator;
	_map->init(BOSSMAPX, BOSSMAPY);
	_map->generateBossMap();

	//ÇÃ·¹ÀÌ¾î
	_player = new player;
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->init();

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
