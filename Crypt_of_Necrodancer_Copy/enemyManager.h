#pragma once
#include "gameNode.h"
#include "slime.h"
#include "whiteSkeleton.h"
#include "mapGenerator.h"
#include "player.h"
#include <vector>


class enemyManager :public gameNode
{
private:
	player* _player;
	mapGenerator* _map;

	vector<whiteSkeleton*> _vWitheSkeleton;
	vector<whiteSkeleton*>::iterator _viWitheSkeleton;
public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setWhiteSkeleton();

	void setMapGeneratorMemoryAddressLink(mapGenerator* map) {_map = map;}
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
};
