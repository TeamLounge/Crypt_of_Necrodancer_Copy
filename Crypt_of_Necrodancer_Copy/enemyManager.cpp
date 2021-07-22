#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setImage();
	setWhiteSkeleton();
	setGreenSkeleton();
	setBlackSkeleton();
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
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->update(_player->getTileX(), _player->getTileY());
	}
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->update(_player->getTileX(), _player->getTileY());
	}
}

void enemyManager::render()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->render();
	}
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->render();
	}
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->render();
	}
}

void enemyManager::setImage()
{
	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("greenSkeleton", "image/enemy/skeletonYellow.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("blackSkeleton", "image/enemy/skeletonBlack.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ghost", "image/enemy/ghost.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimic", "image/enemy/mimic.bmp", 375, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minotaur", "image/enemy/minotaur.bmp", 1350, 294, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkeyBasic", "image/enemy/monkeyBasic.bmp", 450, 150, 6, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("skeleton_dark", "image/enemy/skeletonBasic_dark.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ghost_dark", "image/enemy/ghost_dark.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimic_dark", "image/enemy/mimic_dark.bmp", 375, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minotaur_dark", "image/enemy/minotaur_dark.bmp", 1350, 294, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monkeyBasic_dark", "image/enemy/monkeyBasic_dark.bmp", 450, 150, 6, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemyAttackX", "image/enemy/enemyAttack.bmp", 360, 138, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyAttackY", "image/enemy/enemyAttack2.bmp", 358, 144, 5, 2, true, RGB(255, 0, 255));
	

}

void enemyManager::setWhiteSkeleton()
{
	for (int i = 0; i < 2; i++)
	{
		whiteSkeleton* _skeleton = new whiteSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vWitheSkeleton.emplace_back(_skeleton);
	}
}

void enemyManager::setGreenSkeleton()
{
	for (int i = 0; i < 2; i++)
	{
		greenSkeleton* _skeleton = new greenSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vGreenSkeleton.emplace_back(_skeleton);
	}

}

void enemyManager::setBlackSkeleton()
{
	for (int i = 0; i < 2; i++)
	{
		blackSkeleton* _skeleton = new blackSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vBlackSkeleton.emplace_back(_skeleton);
	}
}

//void enemyManager::setGhost()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		ghost* _ghost = new ghost;
//		_ghost->setTileMapLinK(_map);
//		_ghost->init(_player->getTileX(), _player->getTileY());
//		_vGhost.emplace_back(_ghost);
//	}
//}

//void enemyManager::setMimic()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		mimic* _mimic = new mimic;
//		_mimic->setTileMapLinK(_map);
//		_mimic->init(_player->getTileX(), _player->getTileY());
//		_vMimic.emplace_back(_skeleton);
//	}
//}
//
//void enemyManager::setMonkey()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		monkey* _skeleton = new monkey;
//		_skeleton->setTileMapLinK(_map);
//		_skeleton->init(_player->getTileX(), _player->getTileY());
//		_vMonkey.emplace_back(_skeleton);
//	}
//}
//
//void enemyManager::setMinotaur()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		blackSkeleton* _skeleton = new blackSkeleton;
//		_skeleton->setTileMapLinK(_map);
//		_skeleton->init(_player->getTileX(), _player->getTileY());
//		_vBlackSkeleton.emplace_back(_skeleton);
//	}
//}
