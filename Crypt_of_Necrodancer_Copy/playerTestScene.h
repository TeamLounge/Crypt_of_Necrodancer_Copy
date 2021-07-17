#pragma once
#include "gameNode.h"
#include "player.h"
#include "mapGenerator.h"

class playerTestScene : public gameNode
{
private:
	mapGenerator* _map;
	player* _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

