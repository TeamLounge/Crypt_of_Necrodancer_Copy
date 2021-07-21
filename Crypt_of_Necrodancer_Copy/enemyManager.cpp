#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setWhiteSkeleton();
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->update(_player->getTileX(),_player->getTileY());
	}
}

void enemyManager::render()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->render();
	}
}

void enemyManager::setWhiteSkeleton()
{
	for (int i = 0; i < 5; i++)
	{
		whiteSkeleton* _skeleton = new whiteSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vWitheSkeleton.emplace_back(_skeleton);
	}
}