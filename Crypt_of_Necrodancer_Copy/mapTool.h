#pragma once
#include "gameNode.h"
#include "tileMap.h"


#define SAMPLETILEMAX 5

#define WALLWIDTH 48
#define WALLHEIGHT 96

#define SAMPLEWALLX 8
#define SAMPLEWALLY1 5
#define SAMPLEWALLY2 4

#define SAMPLETRAPMAX 14
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

struct tagTileSizeInput
{
	RECT rc;
	string str;
	bool isSelect;
};

class mapTool : public gameNode
{
private:
	vector<tagSampleTile> _vSampleTile;
	vector<tagSampleObject> _vSampleTrap;

	tagSampleObject _sampleWall1[SAMPLEWALLX * SAMPLEWALLY1];
	tagSampleObject _sampleWall2[SAMPLEWALLX * SAMPLEWALLY2];

	CATEGORY _category; //보여주는 카테고리
	CATEGORY _currentCategory; //선택된 카테고리
	RECT _categoryRect[3]; //카테고리 양 옆으로 움직이는 화살표, 텍스트 용 렉트


	tagCurrentWall _currentWall; //현재 선택한 벽
	TERRAIN _currentFloor; //현재 선택한 타일
	OBJECT _currentTrap; //현재 선택한 함정 오브젝트

	tileMap* _tileMap; //타일맵 그리는 영역

	tagTileSizeInput _tileSizeInput[2];

	int _ctrSelect; //현재 선택한 것

	RECT _resizeButton;

	RECT _saveButton;
	RECT _loadButton;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setup();

	//OBJECT objSelect(int frameX, int frameY);
	tileMap* getTileMap() { return _tileMap; }

	//샘플들 그리기
	void drawSample();

	//카테고리 화살표, 텍스트 렉트 그리기
	void drawCategory();
};

