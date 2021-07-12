#pragma once
#include "gameNode.h"
#include <vector>

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objectFrameX;
	int objectFrameY;
};

class tileMap : public gameNode
{
	image* _tileBuffer;
	int _tileX, _tileY;

	vector<vector<tagTile>> _tiles;

	bool _isEvenLight;

	float _worldTime;

public:
	virtual HRESULT init();
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();

	void setup();

	void resizeTile(int tileX, int tileY);
	void saveTile();
	void loadTile();

	void drawTerrain(TERRAIN terrain);
	void drawWall(int frameX, int frameY, CATEGORY category);
	void deleteObject();

	OBJECT wallSelect(int frameX, int frameY, CATEGORY category);

	image* getTileBuffer() { return _tileBuffer; }

	vector<vector<tagTile>> getTiles() { return _tiles; }

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
};

