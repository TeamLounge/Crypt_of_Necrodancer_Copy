#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "randomMap.h"
#include "whiteSkeleton.h"
class playGround : public gameNode
{
private:
	mapTool* _mapTool;
	randomMap* _randomMap;
	whiteSkeleton* _skeleton;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();
};

