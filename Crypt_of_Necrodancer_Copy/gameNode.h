#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", BACKGROUNDX, BACKGROUNDY);

enum CTRL
{
	CTRL_SAVE,			//세이브		버튼
	CTRL_LOAD,			//로드		버튼
	CTRL_TERRAINDRAW,	//지형		그리기
	CTRL_WALLDRAW,		//벽 		그리기		
	CTRL_OBJECTDRAW,	//함정		그리기
	CTRL_TORCHDRAW,     //횃불		그리기
	CTRL_ERASER,		//지우개		버튼
	CTRL_END
};

enum PLAYER_ENEMY_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum TERRAIN
{
	DIRT1, DIRT2, BOSS, WATER, SHOP, STAIR_BOSS, STAIR_NONE, EMPTY
};

/*
enum OBJECT
{
	OBJ_NONE, WALL_BASIC, WALL_GOLD, WALL_STONE, WALL_CRACK, WALL_DOOR, WALL_END,
	TR_BOMB, TR_UP, TR_DOWN, TR_LEFT, TR_RIGHT,
	TR_FAST, TR_SLOW, TR_JUMP, TR_DOOR, TR_SPIKE, RED_ITEM_BOX, BLACK_ITEM_BOX, BOX, BARREL
	,ENEMY
};
*/

enum MAP_ITEM
{
	MAP_ITEM_NONE,
	MAP_TORCH_PLUS_1, 
	MAP_TORCH_PLUS_2,
	MAP_TITANUM_SHOVEL,
	MAP_LEATHER_ARMOR,
	MAP_CHAIN_ARMOR,
	MAP_DAGGER,
	MAP_BROADSWORD,
	MAP_RAPIER,
	MAP_LONGSWORD,
	MAP_SPEAR,
	MAP_BOMB,
	MAP_APPLE,
	MAP_CHEESE,
	MAP_COIN10
};

enum CATEGORY
{
	CATEGORY_TERRAIN,
	CATEGORY_WALL1,		//기본으로 깨지는
	CATEGORY_WALL2,		//안 깨지는 + 문
	CATEGORY_OBJECT
};

enum ROOMSTATE
{
	ROOM_BASIC,
	ROOM_SHOP,
	ROOM_BOSS,
	ROOM_START
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

