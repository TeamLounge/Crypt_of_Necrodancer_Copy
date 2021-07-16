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
	
	setImage();

	_mapTool = new mapTool;
	_mapTool->init();
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

	//SCENEMANAGER->update();
	_mapTool->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================

	HPEN myPen = (HPEN)CreatePen(0, 1, RGB(0, 0, 0));
	SelectObject(getMemDC(), myPen);
	_mapTool->render();
	DeleteObject(myPen);

	//SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void playGround::setImage()
{
	//타일맵 이미지
	IMAGEMANAGER->addFrameImage("boss_tile", "image/object/tile/boss.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dirt2_tile", "image/object/tile/dirt2.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shop_tile", "image/object/tile/shop.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("water_tile", "image/object/tile/water.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("stair_miniboss_tile", "image/object/tile/stair_miniboss.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));

	//벽 이미지
	IMAGEMANAGER->addFrameImage("walls", "image/object/walls/walls.bmp", 384, 864, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls1", "image/object/walls/walls1.bmp", 384, 480, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls2", "image/object/walls/walls2.bmp", 384, 384, 8, 4, true, RGB(255, 0, 255));

	//함정 이미지
	IMAGEMANAGER->addFrameImage("bomb_trap", "image/object/trapBomb.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("up_trap", "image/object/trapBounceUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down_trap", "image/object/trapBounceDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left_trap", "image/object/trapBounceLeft.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right_trap", "image/object/trapBounceRight.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fast_trap", "image/object/trapSpeedUp.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slow_trap", "image/object/trapSpeedDown.bmp", 48, 56, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door_trap", "image/object/trapDoor.bmp", 92, 72, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("spike_trap", "image/object/trapSpike.bmp", 126, 68, 3, 2, true, RGB(255, 0, 255));

	//그 외 오브젝트
	IMAGEMANAGER->addFrameImage("red_item_box", "image/object/boxRed.bmp", 96, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("black_item_box", "image/object/boxBlack.bmp", 96, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("box", "image/object/box.bmp", 68, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("barrel", "image/object/barrel.bmp", 80, 48, 2, 1, true, RGB(255, 0, 255));

}
