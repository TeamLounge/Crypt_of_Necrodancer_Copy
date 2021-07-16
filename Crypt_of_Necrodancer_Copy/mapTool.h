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
/*======================  ��     ��   !  ==========================
TERRAIN, OBJECT, CTRL, CATEGORY enum�� gameNode.h�� �ֽ��ϴ�.
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

	CATEGORY _category; //�����ִ� ī�װ�
	CATEGORY _currentCategory; //���õ� ī�װ�
	RECT _categoryRect[3]; //ī�װ� �� ������ �����̴� ȭ��ǥ, �ؽ�Ʈ �� ��Ʈ


	tagCurrentWall _currentWall; //���� ������ ��
	TERRAIN _currentFloor; //���� ������ Ÿ��
	OBJECT _currentTrap; //���� ������ ���� ������Ʈ

	tileMap* _tileMap; //Ÿ�ϸ� �׸��� ����

	tagTileSizeInput _tileSizeInput[2];

	int _ctrSelect; //���� ������ ��

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

	//���õ� �׸���
	void drawSample();

	//ī�װ� ȭ��ǥ, �ؽ�Ʈ ��Ʈ �׸���
	void drawCategory();
};

