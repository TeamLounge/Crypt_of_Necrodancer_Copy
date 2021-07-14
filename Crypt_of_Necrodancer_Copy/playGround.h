#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "randomMap.h"
class playGround : public gameNode
{
private:
	mapTool* _mapTool;
	randomMap* _randomMap;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

