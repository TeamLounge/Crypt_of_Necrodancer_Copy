#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "mapGenerator.h"
#include "UIManager.h"

class playerTestScene : public gameNode
{
private:
	mapGenerator* _map;
	player* _player;
	UIManager* _UIM;
	enemyManager* _em;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

