#pragma once
#include "gameNode.h"
#include "tileMap.h"


#define SAMPLETILEMAX 5

#define WALLWIDTH 48
#define WALLHEIGHT 96

#define SAMPLEWALLX 8
#define SAMPLEWALLY1 5
#define SAMPLEWALLY2 4

#define SAMPLETRAPMAX 8
/*======================  필     독   !  ==========================
TERRAIN, OBJECT, CTRL, CATEGORY enum은 gameNode.h에 있습니다.
==================================================================*/

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


class mapTool : public gameNode
{
private:
	vector<tagSampleTile> _vSampleTile;
	vector<tagSampleObject> _vSampleTrap;

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

