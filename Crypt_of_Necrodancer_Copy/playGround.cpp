#include "stdafx.h"
#include "playGround.h"
#include "aStarTest.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	
	//_mapTool = new mapTool;
	//_mapTool->init();
	//SCENEMANAGER->addScene("에이스타",new aStarTest);
	//SCENEMANAGER->changeScene("에이스타");
	_randomMap = new randomMap;
	_randomMap->init();

	CAMERAMANAGER->setCamera(0,0);

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	//SCENEMANAGER->update();
	//_mapTool->update();
	_randomMap->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() - TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() + TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() - TILESIZE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() + TILESIZE);
	}
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================

	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);
	//_mapTool->render();
	DeleteObject(myPen);
	_randomMap->render();
	//SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//==================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}