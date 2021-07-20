#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "player.h"
#include "enemyManager.h"

struct tagPushedObject
{
	int tileX;
	int tileY;
	OBJECT obj;
};
class objectManager : public gameNode
{
	mapGenerator* _map;
	player* _player;
	enemyManager* _em;

	vector<tagPushedObject> _playerPushedObject; //눌린 오브젝트 복구용

	int _tileX;
	int _tileY;

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

