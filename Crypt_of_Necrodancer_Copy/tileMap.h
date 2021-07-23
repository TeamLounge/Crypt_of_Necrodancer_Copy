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
	bool isEnemy = false;	//Ÿ�� ���� ���ʹ� �ֳľ��� => �� Ÿ���̶� ���� �����������
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

	void drawTerrain(TERRAIN terrain); //Ÿ�� �׸���
	void drawWall(int frameX, int frameY, CATEGORY category); //�� �׸���
	void drawObject(OBJECT obj); //���� �׸���
	void drawTorch(); //�� ���� ȶ�� �׸���
	void deleteObject();

	OBJECT wallSelect(int frameX, int frameY, CATEGORY category); //������ ���� ���� OBJECT ����

	image* getTileBuffer() { return _tileBuffer; }

	vector<vector<tagTile>> getTiles() { return _tiles; }

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
};

