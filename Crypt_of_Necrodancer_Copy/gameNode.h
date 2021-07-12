#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//세이브		버튼
	CTRL_LOAD,			//로드		버튼
	CTRL_TERRAINDRAW,	//지형		버튼
	CTRL_WALLDRAW,		//오브젝트	버튼
	CTRL_OBJDRAW,
	CTRL_ERASER,		//지우개		버튼
	CTRL_END
};

enum TERRAIN
{
	DIRT1, DIRT2, BOSS, WATER, SHOP
};

enum OBJECT
{
	OBJ_NONE, WALL_BASIC, WALL_GOLD, WALL_STONE, WALL_CRACK, WALL_DOOR, WALL_END,
	TR_BOMB, TR_UP, TR_DOWN, TR_LEFT, TR_RIGHT,
	TR_FAST, TR_SLOW, TR_DOOR, TR_SPIKE
};

enum CATEGORY
{
	CATEGORY_TERRAIN,
	CATEGORY_WALL1,
	CATEGORY_WALL2,
	CATEGORY_TRAP
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	//HRESULT 마소 전용 반환형식인데
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();	//그리기 함수

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

