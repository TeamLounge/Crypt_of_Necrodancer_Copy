#include "stdafx.h"
#include "slimeGreen.h"

HRESULT slimeGreen::init()
{
	slime::init();	//상속

	_img = IMAGEMANAGER->findImage("slimeGreen");	//protected!!

	//랜덤 배치
	while (true)
	{

		//랜덤방에 배치
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// 그 방이 플레이어방이거나 상점이면 컨티뉴

		//_map->getTileObject	//object인 거 받아오기
		//_map->getTileTerrain	//terrain인 거 받아오기
		//_map->getRect			//타일 rect 받아오기
		//등등 다양한 정보 받아올 수 있으니 잘 쓰자!!!!


		//랜덤하게 찍은 방안의 좌표 중 벽이 있어도 컨티뉴
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y) != OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue;
		break;		//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져 나오기

	}

	_rc = _map->getRect(_x, _y);


	return S_OK;
}

void slimeGreen::update()
{
	slimeMove();
}

void slimeGreen::release()
{
}

void slimeGreen::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom - _rc.top) / 2, 0, 0);
}
