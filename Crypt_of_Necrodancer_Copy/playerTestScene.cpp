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
	//_map->update();
	_player->update();
	
}

void playerTestScene::render()
{
	_map->render();
	_player->render();
}
