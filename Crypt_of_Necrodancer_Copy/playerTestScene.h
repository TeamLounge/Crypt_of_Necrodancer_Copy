#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "mapGenerator.h"
#include "UIManager.h"
#include "objectManager.h"
#include "weapon.h"
#include "shovel.h"
#include "shopkeeper.h"

class playerTestScene : public gameNode
{
private:
	mapGenerator* _map;
	player* _player;
	UIManager* _UIM;
	enemyManager* _em;
	objectManager* _objectManager;
	weapon* _weapon;
	shovel* _shovel;

	shopkeeper* _shopkeeper;

	int stairBossX, stairBossY;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

