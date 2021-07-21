#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{
	_direction = NONE;
	_isRight = true;

	_gravity = 0;
	_jumpPower = 0;

	setImage();

	return S_OK;
}

void slime::release()
{
}

void slime::update()
{

	//플레이어 위치 파악
	//따라가기 혹은 제자리 뛰기
}

void slime::render()
{

}

void slime::slimeMove()
{
	_rc = _map->getRect(_x, _y);	//slime의 _x, _y 좌표를 타일 값으로 받아온다


}

void slime::setImage()
{
	IMAGEMANAGER->addFrameImage("slimeGreen", "image/enemy/slimeGreen.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGreen_dark", "image/enemy/slimeGreen_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("slimeBlue", "image/enemy/slimeBlue.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeBlue_dark", "image/enemy/slimeBlue_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("slimeGold", "image/enemy/slimeGold.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("slimeGold_dark", "image/enemy/slimeGold_dark.bmp", 312, 150, 4, 2, true, RGB(255, 0, 255), true);
}
