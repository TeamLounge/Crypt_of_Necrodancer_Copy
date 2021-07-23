#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "mapGenerator.h"
#include "randomMap.h"

struct tagVision
{
	int tileX, tileY;
	int lightNum;
	bool isSearched;
	bool isWall;
};

class vision : public gameNode
{
private:
	int _tileX, _tileY;
	int _startLightNum;
	tagVision _visionSearch[VISIONY][VISIONX];
	mapGenerator* _map;

public :
	virtual HRESULT init(int tileX, int tileY, int lightNum);
	virtual void release();
	virtual void update(int tileX, int tileY);
	virtual void render();

	void searchSurround();

	void setTileAlpha();

	//void setVisionMapMemoryAddressLink(mapGenerator* map) { _map = map; }
	void setVisionMapMemoryAddressLink(mapGenerator* map) { _map = map; }

	void setStartLightNum(int num) { _startLightNum = num; }

	void setSearchBoundary();

	int getStartLightNum() { return _startLightNum; }

	void findTorch();

	//void addTorchLight(int x, int y);

	void drawMiniMap();
};

