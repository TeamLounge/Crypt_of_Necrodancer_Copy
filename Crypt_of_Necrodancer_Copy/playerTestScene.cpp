#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	_map = new mapGenerator;
	_map->init(70,70);
	_map->generate(7);
	_player = new player;
	_player->init(_map->getStartRoom().x + 2, _map->getStartRoom().y + 2);
	_player->setPlayerMapMemoryAddressLink(_map);
	_player->setupPlayerRect();
	return S_OK;
}

void playerTestScene::release()
{
}

void playerTestScene::update()
{
	_player->update();
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
	}
}

void playerTestScene::render()
{
	_map->render();
	_player->render();
}
