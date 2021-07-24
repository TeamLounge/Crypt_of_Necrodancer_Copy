#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setWhiteSkeleton();

	setSlimeGreen();
	setSlimeGold();
	setSlimeBlue();

	setGreenSkeleton();
	setBlackSkeleton();

	setGhost();

	setMimic();

	setMonkeyBasic();
	setMonkeyWhite();

	setMinotaur();

	setZombie();

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	updateWhiteSkeleton();
	updateGreenSkeleton();
	updateBlackSkeleton();

	updateMimic();

	updateGhost();

	updateSlimeGreen();
	updateSlimeGold();
	updateSlimeBlue();

	updateMonkeyBasic();
	updateMonkeyWhite();

	updateMinotaur();
	
	updateZombie();

}

void enemyManager::render()
{

	renderWhiteSkeleton();
	renderGreenSkeleton();
	renderBlackSkeleton();

	renderMimic();

	renderGhost();

	renderSlimeGreen();
	renderSlimeGold();
	renderSlimeBlue();

	renderMonkeyBasic();
	renderMonkeyWhite();

	renderMinotaur();

	renderZombie();
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
void enemyManager::updateWhiteSkeleton()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderWhiteSkeleton()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->render();
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
void enemyManager::updateGreenSkeleton()
{
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderGreenSkeleton()
{
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->render();
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
void enemyManager::updateBlackSkeleton()
{
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderBlackSkeleton()
{
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->render();
	}
}

void enemyManager::setSlimeGreen()
{
	for (int i = 0; i < 5; i++)
	{
		slimeGreen* _slimeGreen = new slimeGreen;
		_slimeGreen->setTileMapLink(_map);
		_slimeGreen->init();
		_vSlimeGreen.push_back(_slimeGreen);		//emplace_back..?
	}
}
void enemyManager::updateSlimeGreen()
{
	for (_viSlimeGreen = _vSlimeGreen.begin(); _viSlimeGreen != _vSlimeGreen.end(); ++_viSlimeGreen)
	{
		(*_viSlimeGreen)->update();
	}
}
void enemyManager::renderSlimeGreen()
{
	for (_viSlimeGreen = _vSlimeGreen.begin(); _viSlimeGreen != _vSlimeGreen.end(); ++_viSlimeGreen)
	{
		(*_viSlimeGreen)->render();
	}
}

void enemyManager::setSlimeGold()
{
	for (int i = 0; i < 3; i++)
	{
		slimeGold* _slimeGold = new slimeGold;
		_slimeGold->setTileMapLink(_map);
		_slimeGold->init();
		_vSlimeGold.push_back(_slimeGold);
	}
}
void enemyManager::updateSlimeGold()
{
	for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->update();
	}
}
void enemyManager::renderSlimeGold()
{
	for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->render();
	}
}

void enemyManager::setSlimeBlue()
{
	for (int i = 0; i < 4; i++)
	{
		slimeBlue* _slimeBlue = new slimeBlue;
		_slimeBlue->setTileMapLink(_map);
		_slimeBlue->init();
		_vSlimeBlue.push_back(_slimeBlue);
	}
}
void enemyManager::updateSlimeBlue()
{
	for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->update();
	}
}
void enemyManager::renderSlimeBlue()
{
	for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->render();
	}
}



void enemyManager::setGhost()
{
	for (int i = 0; i < 1; i++)
	{
		ghost* _ghost = new ghost;
		_ghost->setTileMapLinK(_map);
		_ghost->init(_player->getTileX(), _player->getTileY());
		_vGhost.emplace_back(_ghost);
	}
}
void enemyManager::updateGhost()
{
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		(*_viGhost)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderGhost()
{
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		(*_viGhost)->render();
	}
}

void enemyManager::setMimic()
{
	for (int i = 0; i < 1; i++)
	{
		mimic* _mimic = new mimic;
		_mimic->setTileMapLinK(_map);
		_mimic->init(_player->getTileX(), _player->getTileY());
		_vMimic.emplace_back(_mimic);
	}
}
void enemyManager::updateMimic()
{
	for (_viMimic = _vMimic.begin(); _viMimic != _vMimic.end(); ++_viMimic)
	{
		(*_viMimic)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderMimic()
{
	for (_viMimic = _vMimic.begin(); _viMimic != _vMimic.end(); ++_viMimic)
	{
		(*_viMimic)->render();
	}
}

void enemyManager::setMonkeyBasic()
{
	for (int i = 0; i < 1; i++)
	{
		monkeyBasic* _monkey = new monkeyBasic;
		_monkey->setTileMapLinK(_map);
		_monkey->init(_player->getTileX(), _player->getTileY());
		_vMonkeyBasic.emplace_back(_monkey);
	}
}
void enemyManager::updateMonkeyBasic()
{
	for (_viMonkeyBasic = _vMonkeyBasic.begin(); _viMonkeyBasic != _vMonkeyBasic.end(); ++_viMonkeyBasic)
	{
		(*_viMonkeyBasic)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderMonkeyBasic()
{
	for (_viMonkeyBasic = _vMonkeyBasic.begin(); _viMonkeyBasic != _vMonkeyBasic.end(); ++_viMonkeyBasic)
	{
		(*_viMonkeyBasic)->render();
	}
}

void enemyManager::setMonkeyWhite()
{
	for (int i = 0; i < 1; i++)
	{
		monkeyWhite* _monkey = new monkeyWhite;
		_monkey->setTileMapLinK(_map);
		_monkey->init(_player->getTileX(), _player->getTileY());
		_vMonkeyWhite.emplace_back(_monkey);
	}
}
void enemyManager::updateMonkeyWhite()
{
	for (_viMonkeyWhite = _vMonkeyWhite.begin(); _viMonkeyWhite != _vMonkeyWhite.end(); ++_viMonkeyWhite)
	{
		(*_viMonkeyWhite)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderMonkeyWhite()
{
	for (_viMonkeyWhite = _vMonkeyWhite.begin(); _viMonkeyWhite != _vMonkeyWhite.end(); ++_viMonkeyWhite)
	{
		(*_viMonkeyWhite)->render();
	}
}

void enemyManager::setMinotaur()
{
	for (int i = 0; i < 1; i++)
	{
		minotaur* _minotaur = new minotaur;
		_minotaur->setTileMapLinK(_map);
		_minotaur->init(_player->getTileX(), _player->getTileY());
		_vMinotaur.emplace_back(_minotaur);
	}
}
void enemyManager::updateMinotaur()
{
	for (_viMinotaur = _vMinotaur.begin(); _viMinotaur != _vMinotaur.end(); ++_viMinotaur)
	{
		(*_viMinotaur)->update(_player->getTileX(), _player->getTileY());
	}
}
void enemyManager::renderMinotaur()
{
	for (_viMinotaur = _vMinotaur.begin(); _viMinotaur != _vMinotaur.end(); ++_viMinotaur)
	{
		(*_viMinotaur)->render();
	}
}

void enemyManager::setZombie()
{
	for (int i = 0; i < 5; i++)
	{
		zombie* _zombie = new zombie;
		_zombie->setTileMapLink(_map);
		_zombie->init();
		_vZombie.push_back(_zombie);
	}
}

void enemyManager::updateZombie()
{
	for (_viZombie = _vZombie.begin(); _viZombie != _vZombie.end(); ++_viZombie)
	{
		(*_viZombie)->update();
	}
}

void enemyManager::renderZombie()
{
	for (_viZombie = _vZombie.begin(); _viZombie != _vZombie.end(); ++_viZombie)
	{
		(*_viZombie)->render();
	}
}
