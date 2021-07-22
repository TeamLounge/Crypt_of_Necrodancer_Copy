#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	setWhiteSkeleton();

	setSlimeGreen();
	setSlimeGold();
	setSlimeBlue();

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

	updateSlimeGreen();
	updateSlimeGold();
	updateSlimeBlue();
}

void enemyManager::render()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->render();
	}

	renderSlimeGreen();
	renderSlimeGold();
	renderSlimeBlue();
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

void enemyManager::setSlimeGreen()
{
	for (int i = 0; i < 3; i++)
	{
		slimeGreen* _slimeGreen = new slimeGreen;
		_slimeGreen->setTileMapLink(_map);
		_slimeGreen->init();	//ÁÂÇ¥..?
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
	/*for (int i = 0; i < 3; i++)
	{
		slimeGold* _slimeGold = new slimeGold;
		_slimeGold->setTileMapLink(_map);
		_slimeGold->init();
		_vSlimeGold.push_back(_slimeGold);
	}*/
}

void enemyManager::updateSlimeGold()
{
	/*for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->update();
	}*/
}

void enemyManager::renderSlimeGold()
{
	/*for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->render();
	}*/
}

void enemyManager::setSlimeBlue()
{
	/*for (int i = 0; i < 3; i++)
	{
		slimeBlue* _slimeBlue = new slimeBlue;
		_slimeBlue->setTileMapLink(_map);
		_slimeBlue->init();
		_vSlimeBlue.push_back(_slimeBlue);
	}*/
}

void enemyManager::updateSlimeBlue()
{
	/*for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->update();
	}*/
}

void enemyManager::renderSlimeBlue()
{
	/*for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->render();
	}*/
}
