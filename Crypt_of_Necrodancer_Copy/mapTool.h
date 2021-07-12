#pragma once
#include "gameNode.h"
#include "tileMap.h"

//#define TILEX 7	//가로 타일 갯수
//#define TILEY 9	//세로 타일 갯수

//#define TILESIZEX TILESIZE * TILEX	//640 32 * 20
//#define TILESIZEY TILESIZE * TILEY	//640 32 * 20

struct tagSampleTile
{
	RECT rc;
	TERRAIN terrain;
};

struct tagSampleObject
{
	RECT rc;
	OBJECT obj;
	int objectFrameX;
	int objectFrameY;
};

struct tagCurrentWall
{
	int x;
	int y;
};

#define WALLWIDTH 48
#define WALLHEIGHT 96

#define SAMPLEWALLX 8
#define SAMPLEWALLY1 5
#define SAMPLEWALLY2 4

class mapTool : public gameNode
{
private:
	vector<tagSampleTile> _vSampleTile;
	tagSampleObject _sampleWall1[SAMPLEWALLX * SAMPLEWALLY1];
	tagSampleObject _sampleWall2[SAMPLEWALLX * SAMPLEWALLY2];

	//tagTile _tiles[TILEX * TILEY];

	tagCurrentWall _currentWall;

	CATEGORY _category;
	CATEGORY _currentCategory;

	tileMap* _tileMap;

	TERRAIN _currentFloor;
	
	RECT _categoryRect[3];

	float _worldTime;

	bool _isEvenLight;

	int _ctrSelect;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setup();

	//OBJECT objSelect(int frameX, int frameY);
	tileMap* getTileMap() { return _tileMap; }

	void drawSample();
	void drawCategory();
};

