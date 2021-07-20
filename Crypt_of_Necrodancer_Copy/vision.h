#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "mapGenerator.h"

struct tagVision
{
	int tileX, tileY;
	int lightNum;
};

class vision : public gameNode
{
private:
	int _tileX, _tileY;
	int _startLightNum;
	tagVision _visionSearch[21][21];
	mapGenerator* _map;

public :
	virtual HRESULT init(int tileX, int tileY, int lightNum);
	virtual void release();
	virtual void update(int tileX, int tileY);
	virtual void render();

	void searchSurround();

	void setTileAlpha();

	void setVisionMapMemoryAddressLink(mapGenerator* map) { _map = map; };

	void setStartLightNum(int num) { _startLightNum = num; }

	void setSearchBoundary();

	
};
