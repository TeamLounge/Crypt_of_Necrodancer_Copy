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

	SCENEMANAGER->update();
	//_mapTool->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================
	//_mapTool->render();
	//SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}