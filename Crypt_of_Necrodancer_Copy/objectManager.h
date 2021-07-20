#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "player.h"
#include "enemyManager.h"
class objectManager : public gameNode
{
	mapGenerator* _map;
	player* _player;
	enemyManager* _em;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObjectMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setObjectPlayerMemoryAddressLink(player* player) { _player = player; };
	void setObjectEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; };

	void playerObjectCollison();
	void enemyObjectCollison();
};

