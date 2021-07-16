#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//���̺�		��ư
	CTRL_LOAD,			//�ε�		��ư
	CTRL_TERRAINDRAW,	//����		�׸���
	CTRL_WALLDRAW,		//�� 		�׸���		
	CTRL_OBJECTDRAW,		//����		�׸���
	CTRL_ERASER,		//���찳		��ư
	CTRL_END
};

enum TERRAIN
{
	DIRT1, DIRT2, BOSS, WATER, SHOP, STAIR, EMPTY
};

enum OBJECT
{
	OBJ_NONE, WALL_BASIC, WALL_GOLD, WALL_STONE, WALL_CRACK, WALL_DOOR, WALL_END,
	TR_BOMB, TR_UP, TR_DOWN, TR_LEFT, TR_RIGHT,
	TR_FAST, TR_SLOW, TR_JUMP, TR_DOOR, TR_SPIKE, RED_ITEM_BOX, BLACK_ITEM_BOX, BOX, BARREL
};

enum CATEGORY
{
	CATEGORY_TERRAIN,
	CATEGORY_WALL1,
	CATEGORY_WALL2,
	CATEGORY_OBJECT
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();	//�׸��� �Լ�

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

