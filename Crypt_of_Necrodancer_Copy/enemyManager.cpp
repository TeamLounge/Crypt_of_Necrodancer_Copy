#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setImage();
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

void enemyManager::setImage()
{
	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skeleton_dark", "image/enemy/skeletonBasic_dark.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyAttackX", "image/enemy/enemyAttack.bmp", 360, 138, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyAttackY", "image/enemy/enemyAttack2.bmp", 358, 144, 5, 2, true, RGB(255, 0, 255));
}

void enemyManager::setWhiteSkeleton()
{
	for (int i = 0; i < 1; i++)
	{
		whiteSkeleton* _skeleton = new whiteSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vWitheSkeleton.emplace_back(_skeleton);
	}
}