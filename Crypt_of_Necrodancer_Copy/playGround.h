#pragma once
#include "gameNode.h"
#include "mapTool.h"

class playGround : public gameNode
{
private:
	mapTool* _mapTool;
	

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

