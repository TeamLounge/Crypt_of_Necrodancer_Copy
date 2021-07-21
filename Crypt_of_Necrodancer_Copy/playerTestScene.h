#pragma once
#include "gameNode.h"
#include "player.h"
#include "mapGenerator.h"
#include "UIManager.h"
#include "weapon.h"

class playerTestScene : public gameNode
{
private:
	mapGenerator* _map;
	player* _player;
	UIManager* _UIM;
	weapon* _weapon;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

