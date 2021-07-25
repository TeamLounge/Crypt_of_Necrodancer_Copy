#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "mapGenerator.h"
#include "playerTestScene.h"
#include "bossScene.h"
#include "player.h"


class playGround : public gameNode
{
private:
	mapTool* _mapTool;
	mapGenerator* _map;

	player* _player;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();
};

