#pragma once
#include "gameNode.h"
#include <vector>

#define MARGIN 60

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objectFrameX;
	int objectFrameY;
	bool isHaveTorch;
	int alpha;
	bool isSeen;
	bool isBombFired;
	bool isEnemy = false;	//타일 위에 에너미 있냐없냐 => 전 타일이랑 같이 갱신해줘야함
};

class tileMap : public gameNode
{
	image* _tileBuffer;
	int _tileX, _tileY;

	int _savedX, _savedY;

	vector<vector<tagTile>> _tiles;

	bool _isEvenLight;

	float _worldTime;

	float _elapsedSec;

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

	void drawTerrain(TERRAIN terrain); //타일 그리기
	void drawWall(int frameX, int frameY, CATEGORY category); //벽 그리기
	void drawObject(OBJECT obj); //함정 그리기
	void drawTorch(); //벽 위에 횃불 그리기
	void deleteObject();

	OBJECT wallSelect(int frameX, int frameY, CATEGORY category); //선택한 벽에 따른 OBJECT 구분

	image* getTileBuffer() { return _tileBuffer; }

	vector<vector<tagTile>> getTiles() { return _tiles; }

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
};

