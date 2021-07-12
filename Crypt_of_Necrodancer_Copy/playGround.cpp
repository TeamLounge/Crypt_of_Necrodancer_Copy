#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	
	_mapTool = new mapTool;
	_mapTool->init();

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();


	_mapTool->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================���� �� ���̿� �� �׸��ô�==========================
	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);
	_mapTool->render();
	DeleteObject(myPen);
	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}