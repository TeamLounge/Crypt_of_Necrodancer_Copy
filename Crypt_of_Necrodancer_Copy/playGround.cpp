#include "stdafx.h"
#include "playGround.h"
#include "aStarTest.h"

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
	
	//_mapTool = new mapTool;
	//_mapTool->init();
	//SCENEMANAGER->addScene("���̽�Ÿ",new aStarTest);
	//SCENEMANAGER->changeScene("���̽�Ÿ");

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

	SCENEMANAGER->update();
	//_mapTool->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================���� �� ���̿� �� �׸��ô�==========================
	//_mapTool->render();
	//SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}